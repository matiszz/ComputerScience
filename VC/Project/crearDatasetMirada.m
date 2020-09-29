function [caractMira, caractNoMira, entrenamentMira, testingMira] = crearDatasetMirada( ulls, f )
% CrearDatasetMirada crea un dataset de categories de mirada, no mirada, entrenament
% i testing.

    % Obtenim característiques dels ulls i dels no-ulls
    % Cada struct té unes característiques, i tipus, que pot ser ull o noUll
    [caractMira, f] = obtenirCaracteristiquesMirada(ulls, f, 'mirant');
    [caractNoMira, f] = obtenirCaracteristiquesMirada(ulls, f, 'no-mirant');

    % Ara hem de separar entre dades de testing i dades per entrenar el model.
    % coefEntrenament és el percentatge d'imatges per entrenar. 90% dona els
    % millors resultats
    waitbar(0.5, f, 'Creant sets');
    u = numel(caractMira);
    nu = numel(caractNoMira);

    for i = 1 : u
        totJunt(i) = caractMira(i);
    end
    for i = u+1 : u+nu
        totJunt(i) = caractNoMira(i-u);
    end

    barrejat = totJunt(randperm(u+nu));
    coefEntrenament = 0.9;
    limit = floor(coefEntrenament*(u+nu));    
    entrenamentMira = struct2table(barrejat(1 : limit));
    testingMira = struct2table(barrejat(limit+1 : end));
end

