/* 
 * File:   Bin.h
 * Author: arash
 *
 * Created on June 13, 2012, 11:51 AM
 */

#ifndef BIN_H
#define	BIN_H

using namespace std;

class Bin : public virtual Shape2D
{
    
public:       
    
    Bin();
    Bin(const Bin& orig);
    virtual ~Bin();
    
    
    
    
    Bin *parent_bin();
    void set_parent_bin( Bin *value );
    void set_item ( Item *item2D );
    virtual Bin *Root( Bin* bin );
    
    
    virtual void itemsInBin(vector<Item*> &items) = 0;
    virtual void binRemSpace(vector<Bin*> &bins) = 0;
    
    virtual int itemsInBinCount();
    virtual int remsInBinCount();
    
    virtual double binSpaceUsed();
    virtual double remSpaceAvail();
    //this one takes into account how much large space is left over that can perhaps be used for other things
    virtual double adjBinSpaceUsed();
    //in the grand scheme of things where does this bin fall
    virtual double binUtilizationRating() = 0;
    
    virtual void totalChildSpaceUsed( double &used ) = 0;
    virtual void totalRemSpaceAvailable( double &avail) = 0;
    virtual void encodeAsJSON(stringstream &jsonStr, bool isDeep) = 0;
    
    virtual bool operator <( Shape &b) = 0;
    virtual bool operator >( Shape &b) = 0;
    virtual bool operator ==( Shape &b) = 0;
    
protected:
    
    
    Bin *parent_bin_;
    Item *item_;

};

#endif	/* BIN_H */
