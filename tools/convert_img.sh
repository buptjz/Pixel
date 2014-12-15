#依次是缩放、旋转、旋转缩放的变换，需要注意的是旋转时需要填充颜色
#convert函数的参数参考http://www.imagemagick.org/script/convert.php

resize () {
    img_path=$1
    name=$2
    for size in 25 49 76 100 148 203 301
    do
        convert $img_path -resize ${size}% ${name}_size_${size}.jpg
    done
}

rerotate () {
    img_path=$1
    name=$2
    for angle in 30 45 60 90 180 270
    do
        convert $img_path -background black -rotate $angle ${name}_rot_${angle}.jpg
    done
}

re_rot_size(){
    img_path=$1
    name=$2
    for angle in 30 60 90 180 270
    do
        for size in 25 76 100 148 301
        do
            convert ${img_path} -background black -resize ${size}% -rotate $angle ${name}_size_${size}_rot_${angle}.jpg
        done
    done
}

#脚本开始，首先设置图片的位置和输出的名字
root=/Volumes/BigData/Developer/Pixel/data/transformed_imgs/6/
file=f.jpg
name=f

cd $root
resize $file $name
rerotate $file $name
re_rot_size $file $name
