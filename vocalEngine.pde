/*
Be Careful with your speaker volume, you might produce a painful 
feedback. We recommend to wear headphones for this example.

*/

import processing.sound.*;

AudioIn input;
FFT fft;


int scale=1;
int bands = 1024;

// declare a drawing variable for calculating rect width
float r_width;

// Create a smoothing vector
float[] sum = new float[bands];

// Create a smoothing factor
float smooth_factor = 0.2;


void setup() {
  
    size(640,360);
        
    //Create an Audio input and grab the 1st channel
    input = new AudioIn(this, 0);
    
    // start the Audio Input
    input.start();
    
    // Create and patch the FFT analyzer
    fft = new FFT(this, bands);
    fft.input(input);
    
    // Calculate the width of the rects depending on how many bands we have
    r_width = width/float(bands);
  
}      


void draw() {
    background(0);
    
    fill(255);
    // We draw an ellispe coupled to the audio analysis
    ellipse(width/2, height/2, 1*scale, 1*scale);
    
    fft.analyze();
    
    int iMax = 0;
    float maxFFT = 0;

    for (int i = 0; i < bands; i++) {
      
      // smooth the FFT data by smoothing factor
      sum[i] += (fft.spectrum[i] - sum[i]) * smooth_factor;
      
      // draw the rects with a scale factor
      rect( i*r_width, height, r_width, -sum[i]*height*scale );
      
      if (fft.spectrum[i] > maxFFT) {
        maxFFT = fft.spectrum[i];
        iMax = i;
      }
    }
    
    // Red color
    fill(255, 0, 0);
    
    // draw the rects with a scale factor
    rect( iMax*r_width, height, r_width, -sum[iMax]*height*scale );
    println(iMax);
    
}