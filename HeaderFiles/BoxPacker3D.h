/*
 * File:   BoxPacker3D.h
 * Author: arash
 *
 * Created on June 15, 2012, 12:47 PM
 */

#ifndef BOXPACKER3D_H
#define	BOXPACKER3D_H
using namespace std;

class BoxPacker3D : public BoxPacker2D {

public:



    BoxPacker3D();
    BoxPacker3D(const BoxPacker3D& orig);
    virtual ~BoxPacker3D();

    bool packIt( bin_t bin,  item_t item, bin_v_t &bins );


    void splitBinWidth( bin_t bin, item_t item );
    void splitBinHeight( bin_t bin, item_t item );
    void splitBinLength( bin_t bin, item_t item );


protected:


    bool checkFitsConstrWidth(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrHeight(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrLength(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrWidthHeight(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrWidthLength(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsConstrHeightLength(Bin *bin, Item *item, vector<Bin*> &bins);
    bool checkFitsNoConstr(bin_t bin,  item_t item, bin_v_t &bins );
    map<string, double> findSubBinSizes( bin_t bin, item_t item);

};

#endif	/* BOXPACKER3D_H */

