/* made by profil 2011-12-29.
**
** Compile with:
** gcc -Wall -pedantic -std=c99 -lX11 status.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <X11/Xlib.h>

static Display *dpy;

void setstatus(char *str) {
	XStoreName(dpy, DefaultRootWindow(dpy), str);
	XSync(dpy, False);
}

float getfreq(char *file) {
	FILE *fd;
	char *freq; 
	float ret;

	freq = malloc(10);
	fd = fopen(file, "r");
	if(fd == NULL) {
		fprintf(stderr, "Cannot open '%s' for reading.\n", file);
		exit(1);
	}

	fgets(freq, 10, fd);
	fclose(fd);

	ret = atof(freq)/1000000;
	free(freq);
	return ret;
}

char *getdatetime() {
	char *buf;
	time_t result;
	struct tm *resulttm;

	if((buf = malloc(sizeof(char)*65)) == NULL) {
		fprintf(stderr, "Cannot allocate memory for buf.\n");
		exit(1);
	}
	result = time(NULL);
	resulttm = localtime(&result);
	if(resulttm == NULL) {
		fprintf(stderr, "Error getting localtime.\n");
		exit(1);
	}
	if(!strftime(buf, sizeof(char)*65-1, "%a %b %d %H:%M:%S", resulttm)) {
		fprintf(stderr, "strftime is 0.\n");
		exit(1);
	}
	
	return buf;
}

int getbattery() {
        FILE *fp;
        int charge_now;
        fp = fopen("/sys/class/power_supply/BAT0/charge_now", "r");

        fscanf(fp, "%d", &charge_now);
        fclose(fp);

        int charge_full;
        fp = fopen("/sys/class/power_supply/BAT0/charge_full", "r");

        fscanf(fp, "%d", &charge_full);
        fclose(fp);

        if (charge_now < 0) return 100; /* the Curious case of -1000.. */
        return (charge_now * 100) / charge_full;
}

int main(void) {
	char *status;
	float cpu0, cpu1;
	char *datetime;
	int bat0;


	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "Cannot open display.\n");
		return 1;
	}

	if((status = malloc(200)) == NULL)
		exit(1);
	

	for (;;sleep(1)) {
		cpu0 = getfreq("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
		cpu1 = getfreq("/sys/devices/system/cpu/cpu1/cpufreq/scaling_cur_freq");
		datetime = getdatetime();
		bat0 = getbattery();
		snprintf(status, 200, "%0.2f, %0.2f | %d%% | %s", cpu0, cpu1, bat0, datetime);

		free(datetime);
		setstatus(status);
	}

	free(status);
	XCloseDisplay(dpy);

	return 0;
}
