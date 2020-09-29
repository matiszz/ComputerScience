function [ caracteristiques ] = getFeaturesLook( imatge )
    caracteristiques = struct();
    caracteristiques.mitjana = mean2(imatge);
    
    hog = extractHOGFeatures(imatge, 'CellSize', [16 16]);
    [~, s] = size(hog);
    for i = 1 : s
        caracteristiques.(['hog', num2str(i)]) = hog(:,i);
    end
    
    [haar, ~] = haart(imatge);
    [z, s] = size(haar);
    for i = 1 : z
        for j = 1 : s
            caracteristiques.(['haar', num2str(i), num2str(j)]) = hog(i,j);
        end
    end
end