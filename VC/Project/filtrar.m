function [ imgFiltrada ] = filtrar( img )
%Filtrar aplica filtres a la imatge
    
    imgFiltrada = imadjust(img);
    imgFiltrada = histeq(imgFiltrada);
    imgFiltrada = medfilt2(medfilt2(imgFiltrada));
    
end

