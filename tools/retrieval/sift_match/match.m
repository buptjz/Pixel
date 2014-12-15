clc;clear;

QUERY = 'c_rot_30.jpg';

%% CANSTANTS
FEAT_ROOT = '/Volumes/BigData/PixelSetFiles/vlfeat-0.9.19';
STARTUP_SCRIPT = strcat(FEAT_ROOT, '/toolbox/vl_setup.m');
run(STARTUP_SCRIPT);
% DATA_PATH = '/Volumes/BigData/Developer/Pixel/data/img_sets/1';
DATA_PATH = '/Volumes/BigData/Developer/Pixel/data/transformed_imgs/all/';

%% qury image
Ia = imread(fullfile(DATA_PATH,QUERY)) ;
[fa,da] = vl_sift(im2single(Ia)) ;

%% candidates 
images = dir(fullfile(DATA_PATH,'*.jpg'));

for i=1:length(images)
    
    Ib = imread(fullfile(DATA_PATH,images(i).name)) ;
    [fb,db] = vl_sift(im2single(Ib)) ;
    [matches, scores] = vl_ubcmatch(da,db) ;
%     [~, perm] = sort(scores, 'descend') ;
%     matches = matches(:, perm) ;
%     scores  = scores(perm) ;
    matching_scores(i) = size(matches, 2);
    images_name{i} = images(i).name;
    fprintf(strcat(int2str(matching_scores(i)),' ',images(i).name,'\n'));
end

%% Ωµ–Ú≈≈¡–£¨ ‰≥ˆ
[~, perm] = sort(matching_scores, 'descend') ;
matching_scores = matching_scores(perm) ;
images_name  = images_name(perm) ;

figure;
subplot(4,5,1);
imshow(Ia);
title(strcat('°æ‘≠°ø',int2str(size(fa,2))));
for j=1:19
    subplot(4,5,j+1);
    img = imread(fullfile(DATA_PATH,images_name{j}));
    imshow(img);
    title(strcat(int2str(int32(matching_scores(j))),' ',images_name{j}));
end


