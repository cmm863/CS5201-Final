#pragma once

template <typename T>
MathVector<T> QRSolver::operator()(const DenseMatrix<T>& m, const MathVector<T>& s)
{
  DenseMatrix<T> Q, Qt, A;
  UpperTriMatrix<T> R;
  QRDecomp qr;
  qr(m, Q, R);
  Qt = DenseMatrix<T>(Q.transpose());

  MathVector<T> b = Qt * s;
  A = DenseMatrix<T>(R.clone());
  GaussianSolver gs;
  return gs(A, b);
}