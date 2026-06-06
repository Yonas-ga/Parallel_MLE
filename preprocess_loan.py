import pandas as pd, numpy as np

df = pd.read_csv('loan.csv')
target = 'Loan Status'
drop_cols = ['ID','Batch Enrolled','Sub Grade','Loan Title',
             'Total Received Interest','Total Received Late Fee','Recoveries',
             'Collection Recovery Fee','Collection 12 months Medical',
             'Total Collection Amount']

y = df[target].astype(int)
X = df.drop(columns=drop_cols + [target])

num_cols = X.select_dtypes(include='number').columns.tolist()
cat_cols = X.select_dtypes(include='object').columns.tolist()

Xn = X[num_cols].astype(float)

stds = Xn.std()
constant = stds[stds == 0].index.tolist()
if constant:
    print("dropping constant numeric columns:", constant)
Xn = Xn[[c for c in num_cols if c not in constant]]
Xn = (Xn - Xn.mean()) / Xn.std()

Xc = pd.get_dummies(X[cat_cols], drop_first=True).astype(float)

feat = pd.concat([Xn, Xc], axis=1)
out = pd.concat([y.rename('outcome'), feat], axis=1).dropna()

out.to_csv('clean_loan.csv', index=False, header=False)
print("rows after dropna:", len(out))
print("number of features:", feat.shape[1], " -> p =", feat.shape[1] + 1, "(with intercept)")

# reference of sklearn estimation
from sklearn.linear_model import LogisticRegression
M = np.loadtxt('clean_loan.csv', delimiter=',')
yv, Xv = M[:,0], M[:,1:]
clf = LogisticRegression(penalty=None, max_iter=2000)
clf.fit(Xv, yv)
print("\nsklearn reference (models P(default=1)):")
print("  intercept:", round(float(clf.intercept_[0]),4))
print("  first 6 coefs:", np.round(clf.coef_[0][:6],4))
print("  train accuracy:", round(clf.score(Xv,yv),4))