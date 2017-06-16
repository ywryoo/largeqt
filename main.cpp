/// @author Ryangwook Ryoo, 2017
/// @email ywryoo@gmail.com
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)

#include <QApplication>
#include "mainwindow.h"
#include <stdlib.h>
#include <stdio.h>
#include "workerthread.h"
int ArgPos(char *str, int argc, char **argv) {
	int a;
	for (a = 1; a < argc; a++) if (!strcmp(str, argv[a])) {
		if (a == argc - 1) {
			printf("Argument missing for %s\n", str);
			exit(1);
		}
		return a;
	}
	return -1;
}


int main( int argc, char **argv )
{
    int i;
    int isCliOnly = 0;

    if ((i = ArgPos((char *)"-cli", argc, argv)) > 0) isCliOnly = atoi(argv[i + 1]);


    if(isCliOnly == 1)
    {
        char infile[1000], labelfile[1000], outfile[1000];
        int prop, pmethod, threads, pipelining, bhsne, trees, rseed, knnval, sleeping, fitting_threading, max_iter, early_iter;
        unsigned int bins;
        double theta, perp,learn,srate;

        strcpy(infile, "data.txt");
        strcpy(labelfile, "label.txt");
        strcpy(outfile, "");
        theta = 0.5;
        perp = 50;
        trees = -1;
        rseed = 13;
        knnval = 1;
        prop = 3;
        pmethod = 0;
        threads = 4;
        pipelining = 1;
        bins = 512;
        sleeping = 1;
        fitting_threading = 1;
        bhsne = 1;
        srate = 20;
        learn = 200.0;
        max_iter = 1000;
        early_iter = 250;
        
        if ((i = ArgPos((char *)"-input", argc, argv)) > 0) strcpy(infile, argv[i + 1]);
        if ((i = ArgPos((char *)"-label", argc, argv)) > 0) strcpy(labelfile, argv[i + 1]);
        if ((i = ArgPos((char *)"-output", argc, argv)) > 0) strcpy(outfile, argv[i + 1]);
        if ((i = ArgPos((char *)"-theta", argc, argv)) > 0) theta = atof(argv[i + 1]);
        if ((i = ArgPos((char *)"-perp", argc, argv)) > 0) perp = atof(argv[i + 1]);
        if ((i = ArgPos((char *)"-trees", argc, argv)) > 0) trees = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-rseed", argc, argv)) > 0) rseed = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-knnval", argc, argv)) > 0) knnval = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-sleep", argc, argv)) > 0) sleeping = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-fthread", argc, argv)) > 0) fitting_threading = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-prop", argc, argv)) > 0) prop = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-pmethod", argc, argv)) > 0) pmethod = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-threads", argc, argv)) > 0) threads = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-pipelining", argc, argv)) > 0) pipelining = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-bins", argc, argv)) > 0) bins = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-bhsne", argc, argv)) > 0) bhsne = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-learn", argc, argv)) > 0) learn = atof(argv[i + 1]);
        if ((i = ArgPos((char *)"-maxiter", argc, argv)) > 0) max_iter = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-earlyiter", argc, argv)) > 0) early_iter = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-srate", argc, argv)) > 0) srate = atof(argv[i + 1]);
        WorkerThread *thread = new WorkerThread;
        thread->runrun(QString(infile), QString(labelfile), QString(outfile), prop, theta, perp, bins, pmethod, rseed, threads, pipelining == 1 ? true : false,knnval == 1 ? true : false, trees, sleeping == 1 ? true : false, fitting_threading == 1 ? true : false, bhsne == 1 ? true : false, learn, max_iter, early_iter, true,srate);
        if(!QString(outfile).isEmpty())
        {

            FILE* fp_saved = fopen(QString(outfile).append("_variables.txt").toUtf8().constData(), "w+");
            char temp_str[1000] = "";                    
            sprintf(temp_str, "Input file: %s\n", infile);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Output file: %s\n", outfile);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Label file: %s\n", labelfile);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Theta: %lf\n", theta);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Perplexity: %lf\n", perp);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Number of RPTrees: %d\n", trees);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Random Seed: %d\n", rseed);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "KNN Validation(1 is on): %d\n", knnval);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Sleeping(1 is on): %d\n", sleeping);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Threading Fitting(1 is on): %d\n", fitting_threading);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Number of Propagation: %d\n", prop);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "P method(0 is RPTrees, 1 is VP Tree): %d\n", pmethod);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Number of Threads: %d\n", threads);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Pipelining(1 is on): %d\n", pipelining);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "Bins: %d\n", bins);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "isCli: %d\n", isCliOnly);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "bhsneOnly: %d\n", bhsne);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "learning rate: %lf\n", learn);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "max_iter: %d\n", max_iter);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "early_iter: %d\n", early_iter);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            sprintf(temp_str, "srate: %lf\n", srate);
            fwrite(temp_str, strlen(temp_str), 1, fp_saved);
            fclose(fp_saved);
        }
        thread->wait();
        return 0;


    }
    else
    {
        QApplication a( argc, argv );

        MainWindow w( argc, argv );

        w.show();
    
        return a.exec();
    }
}
