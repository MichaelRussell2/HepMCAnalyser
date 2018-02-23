#include <histo.hh>

//FastPartons::Histo::Histo() {}
//FastPartons::Histo::~Histo() {}

FastPartons::Histo::Histo(const double xmin, const double xmax, const double deltax){
  min = xmin;
  max = xmax;
  binWidth = deltax;
  binCount = (int)((max-min)/binWidth);
  counts = vector<double>(binCount,0);
}

//fill histo with number of events only
void FastPartons::Histo::fill(double entry) {
  int bin = (int)((entry - min) / binWidth);
  if (bin < 0) {
    underflowcount++;
  } 
  else if (bin >= binCount) {
    overflowcount++;
  } 
  else {
    counts[bin]+=1.;
  }
}

//fill histo with event weights
void FastPartons::Histo::fill(double entry, double weight) {
  if ( entry < min || entry > max ) return;
  int bin = (int)((entry - min) / binWidth);
  counts[bin]+=weight;
  return;
}

//write out raw histogram
void FastPartons::Histo::write(const char *outfile){
 std::ofstream fout;
 fout.open(outfile);
  for (int i=0; i<binCount; i++){
    fout << lowerBound(i) << "  " << upperBound(i) << "  " << counts[i] << endl;
  }
  fout.close();
  counts.clear();
}

//write out normalised histogram
void FastPartons::Histo::write(const char *outfile, double norm){
 std::ofstream fout;
 fout.open(outfile);
  for (int i=0; i<binCount; i++){
    fout << lowerBound(i) << "  " << upperBound(i) << "  " << counts[i]/norm << endl;
  }
  fout.close();
  counts.clear();
}

double FastPartons::Histo::integral(){
  double area = 0;
  for (int i=0; i<binCount; i++){
    area += counts[i];
  }
  return area;
}

int FastPartons::Histo::bins(){
  return (int)((max-min)/binWidth);
}

double FastPartons::Histo::lowerBound(int bin){
  return (min+bin*binWidth);
}

double FastPartons::Histo::upperBound(int bin){
  return (min+(bin+1)*binWidth);
}

int FastPartons::Histo::count(int bin){
  return (int)counts[bin];
}
