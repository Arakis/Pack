#ifndef NULL
#define NULL   ((void *) 0)
#endif

using namespace std;

BoxPacker2D::BoxPacker2D():Packer()
{
}

BoxPacker2D::BoxPacker2D(const BoxPacker2D& orig)
{
	BoxPacker2D();
}

BoxPacker2D::~BoxPacker2D() 
{

}

void BoxPacker2D::packThem( vector<Bin*> bins, vector<Item*> items )
{

	sort( items.begin(), items.end(), Utils::compareDescShape );

	for( unsigned k=0; k < items.size(); ++k )
	{

		//cout << "items: " <<  ((Item3D*)items[k])->volume() << endl;

		sort(bins.begin(), bins.end(), Utils::compareAscShape);

		bool is_bin_found = false;
		int bin_found_index = 0;
		for( vector<Bin*>::iterator member = bins.begin(); member != bins.end(); member++ )
		{   
			//cout << "bins: "  << dynamic_cast<Bin3D*>(*member)->volume() <<  endl;
			if ( packIt( *member, items[k], bins ) == true) 
			{

				is_bin_found = true;
				break;
			}
			bin_found_index++;
		} 

		if ( is_bin_found == true )
			bins.erase( bins.begin() + bin_found_index ); 
	}

}



bool BoxPacker2D::packIt( Bin *bin, Item *item, vector<Bin*> &bins)
{

	int constraints = item->constraints();    

	if ( constraints == Item2D::CONSTRAINT_WIDTH)
		return checkFitsConstrWidth(bin, item, bins);
	else if ( constraints == Item2D::CONSTRAINT_HEIGHT )
		return checkFitsConstrHeight(bin, item, bins);
	else
		return checkFitsNoConstr(bin, item, bins );



}

bool BoxPacker2D::checkFitsConstrWidth(Bin *bin, Item *item, vector<Bin*> &bins)
{
	Item2D *item2d = dynamic_cast<Item2D*>(item);
	if( item2d->side_1()->size() <= bin->side_1()->size() && 
			item2d->side_2()->size() <= bin->side_2()->size() )
	{

		bin->set_item( item );

		//if it fits split item and recurse
		splitBinWidth( bin, item );
		splitBinHeight( bin, item );

		Bin2D * bin2d = dynamic_cast<Bin2D*>(bin);

		if ( bin2d->x_sub_bin() != NULL )
		{

			bins.push_back( bin2d->x_sub_bin() );

		}
		if( bin2d->y_sub_bin() != NULL )
		{

			bins.push_back( bin2d->y_sub_bin() );
		}

		return true;

	}

	return false;

}

bool BoxPacker2D::checkFitsConstrHeight(Bin *bin, Item *item, vector<Bin*> &bins)
{
	Item2D *item2d = dynamic_cast<Item2D*>(item);
	if( item2d->side_1()->size() <= bin->side_1()->size() && item2d->side_2()->size() <= bin->side_2()->size())
	{

		bin->set_item( item );

		//if it fits split item and recurse
		splitBinWidth( bin, item );
		splitBinHeight( bin, item );
		Bin2D * bin2d = dynamic_cast<Bin2D*>(bin);

		if ( bin2d->x_sub_bin() != NULL )
		{

			bins.push_back( bin2d->x_sub_bin() );

		}
		if( bin2d->y_sub_bin() != NULL )
		{

			bins.push_back( bin2d->y_sub_bin() );
		}


		return true;

	}

	return false;

}

bool BoxPacker2D::checkFitsNoConstr(Bin *bin, Item *item, vector<Bin*> &bins)
{
	Item2D *item2d = dynamic_cast<Item2D*>(item);

	//sort both bin and item
	if ( bin->side_1()->size() < bin->side_2()->size() )
	{

		Side *tmps;
		tmps = bin->side_1();
		bin->set_side_1( bin->side_2() );
		bin->set_side_2( tmps );
	}


	if ( dynamic_cast<Item2D*>(item)->side_1()->size() < dynamic_cast<Item2D*>(item)->side_2()->size() )
	{

		Side *tmps;
		Item2D *item2d = dynamic_cast<Item2D*>(item);
		tmps = item2d->side_1();
		item2d->set_side_1( item2d->side_2() );
		item2d->set_side_2( tmps );
	}


	if( item2d->side_1()->size() <= bin->side_1()->size() && item2d->side_2()->size() <= bin->side_2()->size() )
	{

		bin->set_item( item );

		//if it fits split item and recurse
		splitBinWidth( bin, item );
		splitBinHeight( bin, item );
		Bin2D * bin2d = dynamic_cast<Bin2D*>(bin);

		if ( bin2d->x_sub_bin() != NULL )
		{

			bins.push_back( bin2d->x_sub_bin() );

		}
		if( bin2d->y_sub_bin() != NULL )
		{

			bins.push_back( bin2d->y_sub_bin() );
		}

		return true;

	}

	return false;

}


void BoxPacker2D::splitBinWidth( Bin *bin, Item *item )
{
	Item2D *item2d = dynamic_cast<Item2D*>(item);
	double dx_w = bin->side_1()->size() - item2d->side_1()->size();
	double dx_h = item2d->side_2()->size();

	Bin2D * bin2d = dynamic_cast<Bin2D*>(bin);

	if ( dx_w <= 0 )
		bin2d->set_x_sub_bin( NULL );
	else
	{

		Bin2D *sub_binX = new Bin2D();
		sub_binX->set_side_1( bin->side_1()->size_side_to( dx_w ));
		sub_binX->set_side_2( bin->side_2()->size_side_to( dx_h ));
		sub_binX->set_parent_bin( bin );
		sub_binX->set_id(bin->id());
		bin2d->set_x_sub_bin( sub_binX );


	}


}

void BoxPacker2D::splitBinHeight( Bin *bin, Item *item )
{
	Item2D *item2d = dynamic_cast<Item2D*>(item);
	double dy_w = bin->side_1()->size();
	double dy_h = bin->side_2()->size() - item2d->side_2()->size();

	Bin2D * bin2d = dynamic_cast<Bin2D*>(bin);

	if ( dy_h <= 0 )
		bin2d->set_y_sub_bin( NULL );
	else
	{

		Bin2D *sub_binY = new Bin2D();
		sub_binY->set_side_1( bin->side_1()->size_side_to( dy_w ));
		sub_binY->set_side_2( bin->side_2()->size_side_to( dy_h ));
		sub_binY->set_parent_bin( bin );
		sub_binY->set_id(bin->id());
		bin2d->set_y_sub_bin( sub_binY );


	}

}