#include <stdio.h>
#include <stdlib.h>

#include "./include/fetchme.h"
#include "./include/color.h"

#if LINUX_SUPPORT_ONLY
#include <string.h>
#elif BSD_SUPPORT_ONLY
#include <sys/sysctl.h>
#endif /* string.h or sysctl.h */
int
cpu_info(void)
{
#if LINUX_SUPPORT_ONLY
	// this long line is used to skip lines.
#define ITER(x)                 \
	for (int i = 0; i < x; i++) \
		while ((c = fgetc(cpu)) != '\n' && c != EOF)

	char brand[10]; // cpu brand
	char lineup[10]; // lineup (Ryzen, Core, Xeon, Epyc, etc)
	char sublineup[10]; // sublineup (5, 7, 9 or i5 i7 i9 etc)
	char model_num[10]; // model number (3600, 9900k, 3900X, etc)
	char model_name[16];
	int file = 0;
#ifdef CPU_FREQUENCY
	char freq[10]; // cpu frequency
#endif /* CPU_FREQUENCY */
#ifdef CPU_THREADS
	char threads[10]; // cpu threads
#endif /* CPU_THREADS */
#ifdef CPU_TEMP
	double TEMP;
	FILE *cpu3 = fopen("/sys/class/hwmon/hwmon1/temp1_input", "r");
#endif /* CPU_TEMP */

	int c;

	FILE *cpu = fopen("/proc/cpuinfo", "r");
	if (cpu == NULL) {
		perror("/proc/cpuinfo");
		exit(EXIT_FAILURE);
	}
	/*
     * TODO: this code will eventually
     * be changed to filter out and remove
     * words like `CPU' and `Processor'
     */
	fscanf(cpu, "%15[^\t]\t:", model_name);

	while ((file != EOF) && (strncmp(model_name, "model name", 10) != 0)) {
		ITER(1);
		file = fscanf(cpu, "%15[^\t]\t:", model_name);
	}

	if (file == EOF)
		exit(EXIT_FAILURE);

	fscanf(cpu, "%9s %9s %9s %9s", brand, lineup, sublineup, model_num);
#if defined(CPU_FREQUENCY) || defined(CPU_THREADS) || defined(CPU_TEMP)
	ITER(3);
#ifdef CPU_FREQUENCY
	fscanf(cpu, "%*9s %*9s \t: %9s", freq);
#endif /* CPU_FREQUENCY */
	ITER(3);
#ifdef CPU_THREADS
	fscanf(cpu, "%*9s \t: %9s", threads);
#endif /* CPU_THREADS */
#endif /* CPU_FREQUENCY || CPU_THREADS || CPU_TEMP */
	fclose(cpu);
#ifdef CPU_TEMP

	if (cpu3 == NULL) {
		cpu3 = fopen("/sys/class/hwmon/hwmon1/temp2_input", "r");
		if (cpu3 == NULL) { /* cpu3 is still NULL after entering temp2_input */
			cpu3 = fopen("/sys/class/hwmon/hwmon1/temp3_input", "r");
			if (cpu3 == NULL) {
				TEMP = 0.; /* Ryzen CPU temperature file not found */
			}
		}
	} else {
		char line1_value[100];
		int x2 = 0;
		fscanf(cpu3, "%99s", line1_value);
		fclose(cpu3);
		sscanf(line1_value, "%d", &x2);
		TEMP = (x2 / 1000.);
	}
#endif /* CPU_TEMP */
	if (strcmp(sublineup, "CPU") == 0)
		printf("%sCPU:\033[0m %s %s %s", color_distro(), brand, lineup,
			   model_num);
	else if (strcmp(model_num, "CPU") == 0)
		printf("%sCPU:\033[0m %s %s %s", color_distro(), brand, lineup,
			   sublineup);
	else
		printf("%sCPU:\033[0m %s %s %s %s", color_distro(), brand, lineup,
			   sublineup, model_num);

#ifdef CPU_THREADS
	printf(" (%s)", threads);
#endif /* CPU_THREADS */
#ifdef CPU_FREQUENCY
	printf(" @ %sMHz", freq);
#endif /* CPU_FREQUENCY */
#ifdef CPU_TEMP
	printf(" (%.1f°C)", TEMP);
#endif /* CPU_TEMP */
	printf("\n");
#elif BSD_SUPPORT_ONLY /* linux */
	int mib[2];
	char *cpu_name;
	size_t len;
	mib[0] = CTL_HW;
	mib[1] = HW_MODEL;
	sysctl(mib, 2, NULL, &len, NULL, 0);
	cpu_name = malloc(len);
	if (sysctl(mib, 2, cpu_name, &len, NULL, 0) != 0) {
		perror("sysctl");
		exit(EXIT_FAILURE);
	}
	printf("%sCPU: \033[0m%s\n", color_distro(), cpu_name);
	free(cpu_name);
#endif /* FreeBSD */
	return EXIT_SUCCESS;
}
