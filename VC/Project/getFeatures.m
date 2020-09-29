function [ caracteristiques ] = getFeatures( imatge )
    caracteristiques = struct();
    caracteristiques.mitjana = mean2(imatge);
    
    % Amb 16x16 s'obté una accuracy del 99%
    hog = extractHOGFeatures(imatge, 'CellSize', [16 16]);
    [~, s] = size(hog);
    
    for i = 1 : s
        caracteristiques.(['hog', num2str(i)]) = hog(:,i);
    end
end