#include <QApplication>
#include "mainwindow.h"
#include "pixelsne/pixelsne.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char **argv )
{
/*
    // Define some variables
    int     origN;                  
    int     N;                      
    int     D;                      
    int     no_dims = 2;                
    int*    landmarks;              
	double  perc_landmarks;         
    double  perplexity = 30;
    double  theta = 0.5;                
    double* data;                   
    unsigned int bins;
    int     p_method;
    int rand_seed = 30;            
    PixelSNE* pixelsne = new PixelSNE();

    // #ifdef USE_BITWISE_OP
    //     printf("pixelsne.cpp USE_BITWISE_OP\n");
    // #else
    //     printf("pixelsne.cpp not USE_BITWISE_OP\n");
    // #endif

	//Op
	pexp = (double*)calloc(EXP_LUT_DIV, sizeof(double));
	for (int i = 0; i < EXP_LUT_DIV; i++)
	{
        #ifdef USE_BITWISE_OP
            pexp[i] = exp((double)EXP_LUT_RANGE * ((double)(i << 1) / EXP_LUT_DIV - 1));
        #else
            pexp[i] = exp((double)EXP_LUT_RANGE * ((double)(i * 2) / EXP_LUT_DIV - 1));
        #endif
	}

    // Read the parameters and the dataset
	if(pixelsne->load_data(&data, &origN, &D, &no_dims, &theta, &perplexity, &bins, &p_method, &rand_seed)) {
		// Make dummy landmarks
        N = origN;

        int* landmarks = (int*) malloc(N * sizeof(int));        
        if(landmarks == NULL) { printf("Memory allocation failed!\n"); exit(1); }
        for(int n = 0; n < N; n++) landmarks[n] = n;            

        double* Y = (double*) malloc(N * no_dims * sizeof(double)); 
		double* costs = (double*) calloc(N, sizeof(double));         
        if(Y == NULL || costs == NULL) { printf("Memory allocation failed!\n"); exit(1); }
        
        pixelsne->run(data, N, D, Y, no_dims, perplexity, theta, bins, p_method, rand_seed, false);
		pixelsne->save_data(Y, landmarks, costs, N, no_dims);

        // Clean up the memory
        if (data != NULL){
            free(data); data = NULL;    
        }
		free(Y); Y = NULL;
		free(costs); costs = NULL;
		free(landmarks); landmarks = NULL;
    }
    delete(pixelsne);
	LargeVis model;
    if (if_embed)
        model.load_from_file(infile);
    else
        model.load_from_graph(infile);
	model.run(out_dim, n_threads, n_samples, n_propagation, alpha, n_trees, n_negative, n_neighbors, n_gamma, perplexity);

	model.save(outfile);
*/    
    QApplication a( argc, argv );

   // MainWindow w(model.get_ans(), model.get_n_vertices(), model.get_out_dim());

    MainWindow w;

    w.show();
  //  Dialog dialog;
  //  dialog.show();
//    QPushButton button;
//button.setText("My text");
//button.setToolTip("A tooltip");
//button.show();

    return a.exec();
}
