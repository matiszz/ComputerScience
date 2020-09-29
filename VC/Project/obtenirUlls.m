function [ dadesUlls, f ] = obtenirUlls(f)
%OBTENIRULLS A partir d'un path, obté un struct d'ulls.
% retorna un struct {imatgeUll, pos, mira}

    directoriImatges = dir('images/imgs/*.pgm');
    nImgs = 260; %length(directoriImatges);

    dadesUlls = cell(1, nImgs); %TODO
    [infoMirada, ~, ~] = xlsread('Miram.xlsx', 1, 'E5:E1525');

    for i = 1 : nImgs
        waitbar(i/nImgs, f, 'Obtenint imatges')
        
        % Extraiem nom de la imatge i la posicio dels ulls
        nomImg = directoriImatges(i).name;
        posInfoMat = dlmread(['images/info/', nomImg(1:end-4), '.eye'], '', 1, 0);

        imatge = filtrar(imread(['images/imgs/', nomImg]));
        dadesUlls{i} = struct('mirant', infoMirada(i), 'imatge', imatge, 'posUlls', posInfoMat);
    end
end