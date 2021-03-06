// unit_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cutest.h"


TEST( DimensionalUnits2 )
{
	char* bins = "0:ft:1:1x1";
	char* items = "0:in:0:1250:1x1";

	cWorld W;
	W.Build( bins, items );
	W.Pack();
	CHECK_EQUAL( 1, W.Bins.size() );
	CHECK_EQUAL( 144, W.Bins[0]->itemsInBinCount() );
	CHECK_CLOSE( 1, W.Items[0]->side_1()->size(),0.001);
	CHECK_CLOSE( 1, W.Items[0]->side_2()->size(),0.001);
	CHECK_CLOSE( 12, W.Bins[0]->side_1()->size(),0.001);
	CHECK_CLOSE( 12, W.Bins[0]->side_2()->size(),0.001);

	bins = "0:in:1:1x1";
	items = "0:ft:0:1250:1x1";

	W.Build( bins, items );
    CHECK_EQUAL( 1, W.Bins.size() );
	CHECK_CLOSE( 12, W.Items[0]->side_1()->size(),0.001);
	CHECK_CLOSE( 12, W.Items[0]->side_2()->size(),0.001);
	CHECK_CLOSE( 1, W.Bins[0]->side_1()->size(),0.001);
	CHECK_CLOSE( 1, W.Bins[0]->side_2()->size(),0.001);

}

TEST( ItemQuantity )
{
	BoxBindingsParser *parser = new BoxBindingsParser();

	char *bins = "0:ft:1:5x5x5";
	char *items = "0:ft:0:125:1x1x1";
	vector<Bin*> bins_v;
	vector<Item*> items_v;

	int dim;
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_EQUAL( 125, items_v.size() );

}

TEST( BinQuantity1 )
{

	char *bins = "0:ft:1:2x2";
	char *items = "0:ft:0:125:1x1";

	cWorld W;
	W.Build( bins, items );
	W.Pack();
	CHECK_EQUAL( 1, W.Bins.size() );
	CHECK_EQUAL( 4, W.Bins[0]->itemsInBinCount() );


}
TEST( Bin3DQuantity1 )
{

	char *bins = "0:ft:1:2x2x1";
	char *items = "0:ft:0:125:1x1x1";

	cWorld W;
	W.Build( bins, items );
	W.Pack();
	CHECK_EQUAL( 1, W.Bins.size() );
	CHECK_EQUAL( 4, W.Bins[0]->itemsInBinCount() );

	bins = "0:ft:1:2x2x2";
	items = "0:ft:0:125:1x1x1";

	W.Clear();
	W.Build( bins, items );
	W.Pack();
	CHECK_EQUAL( 1, W.Bins.size() );
	CHECK_EQUAL( 8, W.Bins[0]->itemsInBinCount() );



}
TEST( BinQuantity2 )
{

	char* bins = "0:ft:2:2x2";
	char* items = "0:ft:0:125:1x1";

	cWorld W;
	W.Build( bins, items );
	W.Pack();
	CHECK_EQUAL( 2, W.Bins.size() );
	CHECK_EQUAL( 4, W.Bins[0]->itemsInBinCount() );
	CHECK_EQUAL( 4, W.Bins[1]->itemsInBinCount() );


}
TEST( BinQuantityEndless )
{

	char* bins = "0:ft:-1:2x2";
	char* items = "0:ft:0:125:1x1";

	cWorld W;
	W.Build( bins, items );
	W.Pack();
	CHECK_EQUAL( 32, W.Bins.size() );
	CHECK_EQUAL( 4, W.Bins[0]->itemsInBinCount() );
	CHECK_EQUAL( 4, W.Bins[1]->itemsInBinCount() );


}

TEST( Defragment )
{
	char* bins = "0:ft:0:3x3";
	char* items = "0:ft:0:125:1x2";

	cWorld W;
	W.Build( bins, items );
	W.Pack();
	CHECK_EQUAL( 1, W.Bins.size() );
	CHECK_EQUAL( 4, W.Bins[0]->itemsInBinCount() );

}

TEST( CutList )
{
    cCutList L;
    L.Add( cCut( 1,1,1,2));
    L.Add( cCut( 2,1,2,2));
    CHECK_EQUAL( 2, L.size());

    L.Add( cCut( 1,2,1,1));
    CHECK_EQUAL( 2, L.size());

    L.Add( cCut( 1,2,1,3));
    CHECK_EQUAL( 3, L.size());
    L.Join();
    CHECK_EQUAL( 2, L.size());


}

TEST( BinCutList )
{
	char *bins = "0:ft:1:2x2";
	char *items = "0:ft:0:1:1x1";

	cWorld W;
	W.Build( bins, items );
	W.Pack();
	cCutList L;
	W.Bins[0]->CreateCutList( L );
	CHECK_EQUAL( 4, L.size());

   cout << L.get();

}
TEST( BinCutList2 )
{
	char *bins = "0:ft:1:2x2";
	char *items = "0:ft:0:2:1x1";

	cWorld W;
	W.Build( bins, items );
	W.Pack();
	cCutList L;
	W.Bins[0]->CreateCutList( L );
	CHECK_EQUAL( 5, L.size());

   cout << L.get();

}
int main(int argc, char *argv[])
{
	return raven::set::UnitTest::RunAllTests();

}

