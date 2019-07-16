clear;clc;
a = imread('1.jpg');
a_hsv = rgb2hsv(a);
imagey = a_hsv(:,:,3);

[r, c, m]=size(a);
b = a;
mask = a;
gamma = zeros(r,c,m);
mask(:) = 255 - a(:);

mask = double(mask)/255;
sigma = [3 0.1];    %·½²î
w = 5;
mask1 = bfilter2(mask,w,sigma);  
gamma(:) = power( 2, (128 - double(mask1(:)*255)) /128.0 );
b(:) = 255*power( double(a(:))/255.0 ,gamma(:) );

imshow(a);figure,imshow(b);