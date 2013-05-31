#ifndef NULL
#define NULL   ((void *) 0)
#endif

/* 
 * File:   Bin1D.cpp
 * Author: arash
 * 
 * Created on June 13, 2012, 11:23 AM
 */
using namespace std;

Bin1D::Bin1D():Bin() {
    
    z_sub_bin_ = NULL;
   
}

Bin1D::Bin1D(const Bin1D& orig) {
    
    Bin1D();
}

Bin1D::~Bin1D() {
    
    if ( z_sub_bin_ != NULL )
        delete z_sub_bin_;
}



Bin *Bin1D::z_sub_bin()
{
    return z_sub_bin_;
};

void Bin1D:: set_z_sub_bin(Bin *value)
{
    z_sub_bin_ = value;
};

void Bin1D:: itemsInBin( vector<Item*> &items)
{
    if ( item_ != NULL)
        items.push_back( item_ );
   
    if ( z_sub_bin_ != NULL )
        z_sub_bin_->itemsInBin( items );
    
    
}



void Bin1D:: binRemSpace( vector<Bin*> &bins)
{
    if ( item_ == NULL )
        bins.push_back( this );
    
    if ( z_sub_bin_ != NULL )
        z_sub_bin_->binRemSpace( bins );
   
    
    
}





void Bin1D:: totalChildSpaceUsed( double &used )
{
    if ( item_ != NULL )
        used += dynamic_cast<Item2D*>(item_)->area();
    
    if ( z_sub_bin_ != NULL )
        z_sub_bin_->totalChildSpaceUsed( used );
    
}



void Bin1D:: totalRemSpaceAvailable(double& avail)
{
    if ( item_ == NULL )
        avail += area();
    
    if ( z_sub_bin_ != NULL )
        z_sub_bin_->totalRemSpaceAvailable( avail );
   
    
}


void Bin1D::encodeAsJSON(stringstream &jsonStr, bool isDeep)
{
    
    jsonStr << "{\"bin_size\": \"" << origSize() << "\",";
    jsonStr << "\"id\": \"" << id_ << "\",";
    jsonStr << "\"size_1\": " << origSide1()->size() << ","; 
    jsonStr << "\"size_2\": " << origSide2()->size() << ",";
    jsonStr << "\"items_count\": " << itemsInBinCount() << ",";
    jsonStr << "\"rems_count\": " << remsInBinCount() << ",";
    jsonStr << "\"bin_perc_used\": " << binSpaceUsed() << ",";
    jsonStr << "\"rem_perc_avail\": " << remSpaceAvail() << ",";
    jsonStr << "\"total_size\": " << area() << ",";
    
    vector<Item*> items;
    itemsInBin(items);
   
    
    jsonStr << "\"items\": [";
    for(unsigned i=0; i < items.size(); ++i)
    {
        items[i]->encodeAsJSON(jsonStr);
        
        if( i != items.size() - 1)
            jsonStr << ",";
    }
    
    items.clear();
    jsonStr << "],";
    
    vector<Bin*> bins;
    binRemSpace(bins);
    
    jsonStr << "\"rems\": [";
    for(unsigned i=0; i < bins.size(); ++i)
    {
        Bin1D * bin1d = dynamic_cast<Bin1D*>(bins[i]);
        jsonStr << "{";
        jsonStr << "\"rem_size\": \"" << bin1d->origSize() << "\",";
        jsonStr << "\"size_1\": " << bin1d->origSide1()->size() << ",";
        jsonStr << "\"size_2\": " << bin1d->origSide2()->size();
        jsonStr << "}";
        
        if( i != bins.size() - 1)
            jsonStr << ",";
    }
    
    bins.clear();
    jsonStr << "]";
    
    if (isDeep)
    {
        jsonStr << ",";
        if (item_ == NULL)
            jsonStr << "\"item\": {},";
        else
        {
            jsonStr << "\"item\": "; 
            item_->encodeAsJSON(jsonStr);
            jsonStr << ",";

        }
        if ( z_sub_bin_ == NULL)
            jsonStr << "\"z_sub_bin\": {}";
        else
        {
            jsonStr << "\"z_sub_bin\": ";        
            z_sub_bin()->encodeAsJSON( jsonStr, isDeep );

        }
    }
    
    jsonStr << "}";
       
}

bool  Bin1D:: operator <( Shape &b) 
{
    Bin1D *bin = dynamic_cast<Bin1D*>(&b);
    
    return this->binUtilizationRating() < bin->binUtilizationRating();
    
}

bool  Bin1D:: operator >( Shape &b)
{ 
    Bin1D *bin = dynamic_cast<Bin1D*>(&b);
    
    return this->binUtilizationRating() > bin->binUtilizationRating();
    
}

bool  Bin1D:: operator ==( Shape &b)
{
    Bin1D *bin = dynamic_cast<Bin1D*>(&b);
    
    return this->binUtilizationRating() == bin->binUtilizationRating();
    
}

double Bin1D::binUtilizationRating()
{
    
    if ( binSpaceUsed() != 0)
        return binSpaceUsed() * area();
    else
        return area();
}

