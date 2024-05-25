import os
import pandas as pd
from sklearn.model_selection import train_test_split
import warnings
from sklearn.tree import DecisionTreeClassifier
warnings.filterwarnings('ignore')
from sklearn.metrics import accuracy_score
from make_input import inputs as inputs


def decision_tree_gini(data,criter,split,maxi_features,maxi_depth,best):
    
    X_train, X_val, y_train, y_val, X_test, y_test=data
    
    clf_gini = DecisionTreeClassifier(criterion=criter,splitter=split,max_depth=maxi_depth,max_features=maxi_features)
    
    clf_gini.fit(X_train, y_train)
    
    y_pred_gini = clf_gini.predict(X_test)
    
    
    print(accuracy_score(y_test, y_pred_gini)*100)
    
    if accuracy_score(y_test, y_pred_gini)>best[0]:
        best=[accuracy_score(y_test, y_pred_gini)*100,criter,split,maxi_features,maxi_depth]
        
    return best

 

pasx=['50','75','25']
nbs=['80','160','320','400']


critere=['gini','entropy','log_loss']
splitter=['best','random']
max_depth=[None,5]
max_features=[None,'sqrt','log2']

with open("../txt_comparaison/decision_tree_comparaison.txt", "w") as f:
    for p in pasx:
        for n in nbs:
            df=None
            for fich in os.listdir(f'../input_selector/{p}/{n}/'):
        
        
                f.write(rf'  {os.linesep}  {os.linesep}')
                f.write(rf'{p} {n} {os.linesep}')
                data=pd.read_csv(f'../input_selector/{p}/{n}/all/df.txt',header=0)
                
                
                input=inputs(data)
               
                best_para=[0,None]
                for criterion in critere:
                    for split in splitter:
                        for maxi_cara in max_features:
                            for depth in max_depth:
                                best_para=decision_tree_gini(input,criterion,split,maxi_cara,depth,best_para)
                                
                f.write(fr'Toute caracteristique best parametre decision tree: {best_para} {os.linesep}')
                
                                
                                


