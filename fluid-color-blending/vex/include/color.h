// COLOR blending lib
// convert to RYB CMYK YUV CIE_Lab CIE_XYZ 

vector4 RGB2CMYK(vector col_rgb;)
{ 
    //convert rgb vakues to cmyk values
    //rgb vector must be normalized from 0 to 1 

    float c = clamp(1-col_rgb.x,0,1);
    float m = clamp(1-col_rgb.y,0,1);
    float y = clamp(1-col_rgb.z,0,1);
    float k = min(c,min(m, y));

    if(k == 1.0)
    {
        return set(0,0,0,1);
    }
    else
    {
        return set((c-k)/(1-k), (m-k)/(1-k), (y-k)/(1-k), k);
    }
 
}

vector CMYK2RGB(vector4 col_cmyk;)
{

    float red = ((1-col_cmyk.x) * (1-col_cmyk.w) );
    float green = ((1-col_cmyk.y) * (1-col_cmyk.w) );
    float blue = ((1-col_cmyk.z) * (1-col_cmyk.w) );

    return set(red, green, blue);
}

vector4 mix_color(vector4 colorA ; vector4 colorB; float qa ; float qb; float recover ; )
{
    float _qb = clamp(qb, 0, 1) ;
    float recover_a = recover * qa ; 
    
    if(qa == 0) return colorB;

    return   (colorA * qa + colorB * _qb * (1 - recover_a)) / (clamp( qa + _qb ,0, 1) + max( qa + _qb - 1, 0) * 0.5);
}

vector mix_color(vector colorA ; vector colorB; float qa ; float qb; float recover ; )
{

    qb = clamp(qb,0,1) ;
    float recover_a  =recover * qa ; 
    
    if(qa==0) {
        return colorB;
    }

    return    (colorA * qa + colorB * qb*(1-recover_a)) /( qa+qb*(1-recover_a) ) ;
}

vector rgb2ryb(vector col;)
{
        // Remove the whiteness from the color.
        float w = float(min(col.x, col.y, col.z)) ;
        float r = float(col.x) - w ;
        float g = float(col.y) - w ;
        float b = float(col.z) - w ;

        float mg = max(r, g, b) ;

        // Get the yellow out of the red+green.
        float y = min(r, g) ;
        r -= y ;
        g -= y ;

        // If this unfortunate conversion combines blue and green, then cut each in half to preserve the value's maximum range.
        if( b>0 && g>0 )
        {
                b /= 2.0 ;
                g /= 2.0 ;
                    }   
        // Redistribute the remaining green.
        y += g ;
        b += g ;

        // Normalize to values.
        float my = max(r, y, b) ;
        if ( my > 0 )
        {
                float n = mg / my ;
                r *= n ;
                y *= n ;
                b *= n ;
        }

        // Add the white back in.
        r += w ;
        y += w ;
        b += w ;

        // And return back the ryb typed accordingly.
        return set( r, y, b) ;
}

vector ryb2rgb( vector col; )
{
        // Remove the whiteness from the color.
        float w = float(min(col.x , col.y, col.z)) ;
        float r = float(col.x) - w ;
        float y = float(col.y) - w ;
        float b = float(col.z) - w ;

        float my = max(r, y, b) ;

        // Get the green out of the yellow and blue
        float g = min(y, b) ;
        y -= g ;
        b -= g ;

        if (b>0 && g<0)
        {
            b *= 2.0 ;
            g *= 2.0;
        }

        // Redistribute the remaining yellow.
        r += y ;
        g += y ;

        // Normalize to values.
        float mg = max(r, g, b) ;
        if (mg>0)
        {
                float n = my / mg ;
                r *= n ;
                g *= n ;
                b *= n ;
        }

        // Add the white back in.
        r += w ;
        g += w ;
        b += w ;

        // And return back the ryb typed accordingly.
        return set(r,g,b) ;
}
