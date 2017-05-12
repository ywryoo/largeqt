/*
   Copyright 2016 LargeVis authors

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   Modified by Ryangwook Ryoo
*/
#include "mainwindow.h"
#include "plot.h"
#include "borderlayout.h"
#include <QTextBrowser>
#include <QLabel>
#include <QtWidgets>
#include <QPushButton>
#include "workerthread.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MainWindow::MainWindow(int argc, char **argv)
{
    char infile[1000], labelfile[1000], outfile[1000];
    int prop, pmethod, threads, pipelining, trees, rseed, knnval;
    unsigned int bins;
    double theta, perp;

	long long i;

    strcpy(infile, "data.txt");
    strcpy(labelfile, "label.txt");
    strcpy(outfile, "");
    theta = 0.5;
    perp = 50;
    trees = -1;
    rseed = 30;
    knnval = 1;
    prop = 3;
    pmethod = 0;
    threads = 4;
    pipelining = 1;
    bins = 512;
    sleep = 0;

    if(argc < 3)
    {
        printf("GUI Mode is used if no args are provided. You can instantly run  largeqt by using these options\n");
        printf("-input: Input file of feature vectors\n");
        printf("-label: Label file for input file\n");
        printf("-output: If specified, full logs will be written\n");
        printf("-theta: Used in PixelSNE. Default is 0.5\n");
        printf("-perp: The perplexity used for deciding edge weights in K-NNG. Default is 50.\n");
        printf("-trees: Number of random-projection trees used for constructing K-NNG. 50 is sufficient for most cases.\n");
        printf("-rseed: Seed value for random\n");
        printf("-knnval: 1 for on, 0 for off. reduce propagation time. Default is 1\n");
        printf("-sleep: 1 for on, 0 for off. reduce fitting time by sleeping points. Default is 0\n");
        printf("-prop: Number of times for neighbor propagations in the state of K-NNG construction. Default is 3.\n");
        printf("-pmethod: 0 for rptrees, 1 for vptree without multithreading. Default is 0.\n");
        printf("-threads: Number of threads. Default is 4.\n");
        printf("-pipelining: 1 for on, 0 for off. pipelining propagation. default is 1\n");
        printf("-bins: PixelSNE option. Default is 512\n");
    }
    else
    {

        if ((i = ArgPos((char *)"-input", argc, argv)) > 0) strcpy(infile, argv[i + 1]);
        if ((i = ArgPos((char *)"-label", argc, argv)) > 0) strcpy(labelfile, argv[i + 1]);
        if ((i = ArgPos((char *)"-output", argc, argv)) > 0) strcpy(outfile, argv[i + 1]);
        if ((i = ArgPos((char *)"-theta", argc, argv)) > 0) theta = atof(argv[i + 1]);
        if ((i = ArgPos((char *)"-perp", argc, argv)) > 0) perp = atof(argv[i + 1]);
        if ((i = ArgPos((char *)"-trees", argc, argv)) > 0) trees = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-rseed", argc, argv)) > 0) rseed = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-knnval", argc, argv)) > 0) knnval = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-sleep", argc, argv)) > 0) sleep = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-prop", argc, argv)) > 0) prop = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-pmethod", argc, argv)) > 0) pmethod = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-threads", argc, argv)) > 0) threads = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-pipelining", argc, argv)) > 0) pipelining = atoi(argv[i + 1]);
        if ((i = ArgPos((char *)"-bins", argc, argv)) > 0) bins = atoi(argv[i + 1]);

    }
    //scatterplot
    d_plot = new Plot( this );

    //start button -> startPixelSNE
    startButton = new QPushButton("&Start", this);
    QObject::connect(startButton, SIGNAL(clicked()),this, SLOT(startPixelSNE()));

    //restart button -> restartPixelSNE
    QPushButton *restartButton = new QPushButton("&Restart", this);
    QObject::connect(restartButton, SIGNAL(clicked()),this, SLOT(restartPixelSNE()));

    //right panel
    QWidget *formGroupBox = new QWidget;
    QFormLayout *layout = new QFormLayout;

    //input
    QinputLocation = new QLineEdit("");
    QinputLocation->setText(infile);

    //label
    QlabelLocation = new QLineEdit("");
    QlabelLocation->setText(labelfile);

    //theta
    Qtheta = new QDoubleSpinBox();
    Qtheta->setValue(theta);

    //perplexity
    Qperplexity = new QSpinBox();
    Qperplexity->setValue(perp);

    //RP Tree numbers
    Qn_rptrees = new QSpinBox();
    Qn_rptrees->setMinimum(-1);
    Qn_rptrees->setValue(trees);

    //rand_seed
    Qrand_seed = new QSpinBox();
    Qrand_seed->setMinimum(-1);
    Qrand_seed->setValue(rseed);

    //rand_init
    Qknn_validation = new QCheckBox();
    Qknn_validation->setChecked(knnval == 1 ? true : false);

    //n_propagations
    Qn_propagations = new QSpinBox();
    Qn_propagations->setValue(prop);

    //p_method
    Qp_method = new QSpinBox();
    Qp_method->setValue(pmethod);

    //n_threads
    Qn_threads = new QSpinBox();
    Qn_threads->setValue(threads);

    //pipelining
    QPipelining = new QCheckBox();
    QPipelining->setChecked(pipelining == 1 ? true : false);

    //bins
    Qbins = new QSpinBox();
    Qbins->setMaximum(4096);
    Qbins->setMinimum(50);
    Qbins->setValue(bins);

    //add boxes to panel
    layout->addRow(new QLabel(tr("Input Location")), QinputLocation);
    layout->addRow(new QLabel(tr("Label Location")), QlabelLocation);    
    layout->addRow(new QLabel(tr("theta")), Qtheta);
    layout->addRow(new QLabel(tr("perplexity")), Qperplexity);
    layout->addRow(new QLabel(tr("n_rptrees")), Qn_rptrees);
    layout->addRow(new QLabel(tr("rand_seed")), Qrand_seed);
    layout->addRow(new QLabel(tr("knn_validation")), Qknn_validation);
    layout->addRow(new QLabel(tr("n_propagations")), Qn_propagations);
    layout->addRow(new QLabel(tr("p_method")), Qp_method);
    layout->addRow(new QLabel(tr("n_threads")), Qn_threads);
    layout->addRow(new QLabel(tr("pipelining")), QPipelining);    
    layout->addRow(new QLabel(tr("bins")), Qbins);
    layout->addRow(startButton);
    layout->addRow(restartButton);
    formGroupBox->setLayout(layout);

    //console label
    consoleLabel = createLabel("Click Start button to start visualization.");

    //main layout
    BorderLayout *mainLayout = new BorderLayout;
    mainLayout->addWidget(d_plot, BorderLayout::Center);
    //mainLayout->addWidget(createLabel("North"), BorderLayout::North);
    //mainLayout->addWidget(createLabel("West"), BorderLayout::West);
    mainLayout->addWidget(formGroupBox, BorderLayout::East);
    //mainLayout->addWidget(createLabel("East 2") , BorderLayout::East);
    mainLayout->addWidget(consoleLabel, BorderLayout::South);
    setLayout(mainLayout);

    //title
    setWindowTitle(tr("Largeqt"));

    if(argc >= 3)
    {

        thread = new WorkerThread;
        connect(thread, SIGNAL(quit_app()), this, SLOT(on_quit()));
        connect(thread, SIGNAL(updateLabels(int*,int)), this, SLOT(setLabels(int*,int)));
        connect(thread, SIGNAL(updatePoints(double*,int,int)), this, SLOT(setSamples(double*,int,int)));
        connect(thread, SIGNAL(sendLog(QString)), this, SLOT(setConsoleText(QString)) );
        thread->runrun(QString(infile), QString(labelfile), QString(outfile), prop, theta, perp, bins, pmethod, rseed, threads, pipelining == 1 ? true : false,knnval == 1 ? true : false, trees, sleep == 1 ? true : false);
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
            sprintf(temp_str, "Sleeping(1 is on): %d\n", sleep);
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

            fclose(fp_saved);
        }
    }
}

MainWindow::~MainWindow()
{
    if(d_plot != NULL) free(d_plot); d_plot=NULL;
    if(thread != NULL && thread->isRunning()) thread->terminate(); thread->wait();
}

QLabel *MainWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}

void MainWindow::setConsoleText(const QString text)
{
    consoleLabel->setText(text);
}

void MainWindow::setSamples(double* Y, int N, int no_dims)
{
    if(data_labels != NULL)
    {
        d_plot->setSamplesWithLabels(Y, data_labels, N, no_dims);
        d_plot->replot();
    }
    else
    {
        QPolygonF samples;
        if(no_dims == 2) {
            for ( long long i = 0; i < N; i++ )
            {
                samples += QPointF(Y[i*no_dims],Y[i*no_dims+1] );
            }

        }

        d_plot->setSamples( samples );
        d_plot->replot();
    }

}

void MainWindow::setLabels(int* labels, int N)
{
    data_labels = labels;
    int max = 0;
    for(int i = 0; i< N; i++)
        if(max < data_labels[i])
            max = data_labels[i];
    d_plot->setLabels(max+1);
}

void MainWindow::startPixelSNE()
{
    if(thread != NULL && thread->isRunning()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wait!");
        msgBox.setText("PixelSNE is Already running!");
        msgBox.exec();
    } else {
        thread = new WorkerThread;
        connect(thread, SIGNAL(quit_app()), this, SLOT(on_quit()));
        connect(thread, SIGNAL(updateLabels(int*,int)), this, SLOT(setLabels(int*,int)));
        connect(thread, SIGNAL(updatePoints(double*,int,int)), this, SLOT(setSamples(double*,int,int)));
        connect(thread, SIGNAL(sendLog(QString)), this, SLOT(setConsoleText(QString)) );
        thread->runrun(QinputLocation->text(), QlabelLocation->text(), Qn_propagations->value(), Qtheta->value(), Qperplexity->value(), Qbins->value(), Qp_method->value(), Qrand_seed->value(), Qn_threads->value(), QPipelining->isChecked(),Qknn_validation->isChecked(), Qn_rptrees->value(),sleep == 1 ? true : false);
    }
}

void MainWindow::restartPixelSNE()
{
    if(thread != NULL && thread->isRunning()) {
        if(thread->initDone())
        {
            thread->stopWorkers();
            thread->terminate();
            thread->wait();
            thread = NULL;
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wait!");
            msgBox.setText("Try after initialization");
            msgBox.exec();
            return;
        }
    }
    thread = new WorkerThread;
    connect(thread, SIGNAL(quit_app()), this, SLOT(on_quit()));
    connect(thread, SIGNAL(updatePoints(double*,int,int)), this, SLOT(setSamples(double*,int,int)));
    connect(thread, SIGNAL(updateLabels(int*,int)), this, SLOT(setLabels(int*,int)));
    connect(thread, SIGNAL(sendLog(QString)), this, SLOT(setConsoleText(QString)) );
    thread->runrun(QinputLocation->text(), QlabelLocation->text(), Qn_propagations->value(), Qtheta->value(), Qperplexity->value(), Qbins->value(), Qp_method->value(), Qrand_seed->value(), Qn_threads->value(), QPipelining->isChecked(),Qknn_validation->isChecked(), Qn_rptrees->value(),sleep == 1 ? true : false);
}

int MainWindow::ArgPos(char *str, int argc, char **argv) {
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

void MainWindow::on_quit()
{
    if(thread != NULL && thread->isRunning())
    {
        thread->stopWorkers();
        thread->terminate();
        thread->wait();
        thread = NULL;
    }
    close();
    QCoreApplication::quit();
}