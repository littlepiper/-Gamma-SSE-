clear;clc;

a = imread('test.jpg');
a_hsv = rgb2hsv(a);
imagey = a_hsv(:,:,3);

[r, c]=size(imagey);
b = a;
mask = imagey;
image = imagey;
gamma = zeros(r,c);
mask = 1 - mask;
sigma = [3 0.1];    %·½²î
w = 5;
mask1 = bfilter2(mask,w,sigma);  
gamma(:) = power( 2, (128 - double(mask1(:)*255)) /128.0 );
image(:) = power( double(imagey(:)) ,gamma(:) );
a_hsv(:,:,3) = image;
b = hsv2rgb(a_hsv);
imshow(a);figure,imshow(b);