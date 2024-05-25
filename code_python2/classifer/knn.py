from sklearn.neighbors import KNeighborsClassifier 
import os
import pandas as pd
from make_input import inputs as inputs


weigth=['uniform','distance']

algorithme=['auto','ball_tree','kd_tree','brute']

nb_voisins=[3,5,7]
pasx=['50','75','25']
nbs=['80','160','320','400']

with open("../txt_comparaison/knn_comparaison.txt", "w") as f:
    for p in pasx:
        for n in nbs:
            df=None
            for fich in os.listdir(f'../input_selector/{p}/{n}/'):
        
        
                f.write(rf'  {os.linesep}  {os.linesep}')
                f.write(rf'{fich} {os.linesep}')
                data=pd.read_csv(f'../input_selector/{p}/{n}/all/df.txt',header=0)
        
                for alg in algorithme:
                    for w in weigth:
                        for nb_voisin in nb_voisins:
                            f.write(rf'  {os.linesep}  {os.linesep}')
                            f.write(rf'{p} {n} {os.linesep}')
                            X_train, X_val, y_train, y_val, X_test, y_test=inputs(data)
                            knn = KNeighborsClassifier(n_neighbors = nb_voisin,weights=w,algorithm=alg).fit(X_train, y_train) 
                              
                            accuracy = knn.score(X_test, y_test)
                            print(alg,w,nb_voisin,p,n,accuracy)
                            knn_predictions = knn.predict(X_test)  
                            f.write(rf'{alg} {w} {nb_voisin} {p} {n} : {accuracy} {os.linesep}')