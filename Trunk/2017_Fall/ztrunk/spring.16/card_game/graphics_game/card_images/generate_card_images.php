<?php

$path = "./Playing_Cards/PNG-cards-1.3/";
$dir = scandir($path);

array_shift($dir);
array_shift($dir);

foreach($dir as $file){

    $path_parts = pathinfo($file);
    $ext = $path_parts['extension'];
    $name = $path_parts['filename'];
    
    if(strpos($name,'2')>0){
        $name = str_replace('2','',$name);
    }
    
    $name = get_value($name);

    $input = "{$path}{$file}";
    
    // $output = "./large/{$name}.gif";
    // echo $output."\n";
    // exec("convert -resize 500x $input $output");
    
    // $output = "./medium/{$name}.gif";
    // echo $output."\n";
    // exec("convert -resize 250x $input $output");
    
    // $output = "./small/{$name}.gif";
    // echo $output."\n";
    // exec("convert -resize 150x $input $output");
    
    // $output = "./xsmall/{$name}.gif";
    // echo $output."\n";
    // exec("convert -resize 100x $input $output");
    
    // $output = "./xxsmall/{$name}.gif";
    // echo $output."\n";
    // exec("convert -resize 75x $input $output");   
     
    $output = "./tiny/{$name}.gif";
    echo $output."\n";
    exec("convert -resize 40x $input $output");  
}

exec("convert -resize 76x110! back_black.jpg ./tiny/back_black.gif"); 
// exec("convert -resize 76x110! back_black.jpg ./xxsmall/back_black.gif"); 
// exec("convert -resize 101x146! back_black.jpg ./xsmall/back_black.gif");
// exec("convert -resize 151x219! back_black.jpg ./small/back_black.gif");
// exec("convert -resize 251x364! back_black.jpg ./medium/back_black.gif");
// exec("convert -resize 500x back_black.jpg ./large/back_black.gif"); 

exec("convert -resize 76x110! back_red.png ./tiny/back_red.gif"); 
// exec("convert -resize 76x110! back_red.png ./xxsmall/back_red.gif"); 
// exec("convert -resize 101x146! back_red.png ./xsmall/back_red.gif");
// exec("convert -resize 151x219! back_red.png ./small/back_red.gif");
// exec("convert -resize 251xx364! back_red.png ./medium/back_red.gif");
// exec("convert -resize 500x back_red.png ./large/back_red.gif"); 

function get_value($name){
    $suit_value = ['spades'=>0,'hearts'=>1,'diamonds'=>2,'clubs'=>3];
    $face_value = ['ace'=>14,'king'=>13,'queen'=>12,'jack'=>11];
    $name_array = explode('_',$name);
    if(sizeof($name_array)==3){
        list($rank,$suit) = [$name_array[0],$name_array[2]];
    }else{
        return($name);
    }
    if(array_key_exists($rank,$face_value)){
        $rank = $face_value[$rank];
    }
    $suit = $suit_value[$suit];
    $value = $suit * 13 + $rank;
    if($value < 10){
        return '0'.$value;
    }
    return $value;
}