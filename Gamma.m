clear;clc;
a = imread('D:/autocruis/Gamma/zIMG_1.jpg');
a_hsv = rgb2hsv(a);
imagey = a_hsv(:,:,3);

[r, c, m]=size(a);
b = a;
mask = a;
gamma = zeros(r,c,m);
mask(:) = 255 - a(:);
sigma1 = 20;
gausFilter = fspecial('gaussian',[5 5],sigma1);
mask = imfilter(mask,gausFilter,'replicate');

mask = double(mask)/255;
gamma(:) = power( 2, (128 - double(mask(:)*255)) /128.0 );
b(:) = 255*power( double(a(:))/255.0 ,gamma(:) );
imshow(a);figure,imshow(b);
