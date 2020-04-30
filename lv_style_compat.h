/**
 * @file lv_style_compat.h
 *
 */

#ifndef LV_STYLE_COMPAT_H
#define LV_STYLE_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

/**********************
 *      DEFINES
 **********************/

#define LV_FONT_DEFAULT LV_THEME_DEFAULT_FONT_NORMAL

/**********************
 *      TYPEDEFS
 **********************/

/*Border types (Use 'OR'ed values)*/
enum {
    LV_BORDER_NONE     = 0x00,
    LV_BORDER_BOTTOM   = 0x01,
    LV_BORDER_TOP      = 0x02,
    LV_BORDER_LEFT     = 0x04,
    LV_BORDER_RIGHT    = 0x08,
    LV_BORDER_FULL     = 0x0F,
    LV_BORDER_INTERNAL = 0x10, /**< FOR matrix-like objects (e.g. Button matrix)*/
};
typedef uint8_t lv_border_part_t;

/*Shadow types*/
enum {
    LV_SHADOW_BOTTOM = 0, /**< Only draw bottom shadow */
    LV_SHADOW_FULL,       /**< Draw shadow on all sides */
};
typedef uint8_t lv_shadow_type_t;

/**
 * Objects in LittlevGL can be assigned a style - which holds information about
 * how the object should be drawn.
 * 
 * This allows for easy customization without having to modify the object's design
 * function.
 */
typedef struct
{
    uint8_t glass : 1; /**< 1: Do not inherit this style*/

    /** Object background. */
    struct
    {
        lv_color_t main_color; /**< Object's main background color. */
        lv_color_t grad_color; /**< Second color. If not equal to `main_color` a gradient will be drawn for the background. */
        lv_coord_t radius; /**< Object's corner radius. You can use #LV_RADIUS_CIRCLE if you want to draw a circle. */
        lv_opa_t opa; /**< Object's opacity (0-255). */

        struct
        {
            lv_color_t color; /**< Border color */
            lv_coord_t width; /**< Border width */
            lv_border_part_t part; /**< Which borders to draw */
            lv_opa_t opa; /**< Border opacity. */
        } border;

        
        struct
        {
            lv_color_t color;
            lv_coord_t width;
            lv_shadow_type_t type; /**< Which parts of the shadow to draw */
        } shadow;

        struct
        {
            lv_coord_t top;
            lv_coord_t bottom;
            lv_coord_t left;
            lv_coord_t right;
            lv_coord_t inner;
        } padding;
    } body;

    /** Style for text drawn by this object. */
    struct
    {
        lv_color_t color; /**< Text color */
        lv_color_t sel_color; /**< Text selection background color. */
        const lv_font_t * font;
        lv_coord_t letter_space; /**< Space between letters */
        lv_coord_t line_space; /**< Space between lines (vertical) */
        lv_opa_t opa; /**< Text opacity */
    } text;

    /**< Style of images. */
    struct
    {
        lv_color_t color; /**< Color to recolor the image with */
        lv_opa_t intense; /**< Opacity of recoloring (0 means no recoloring) */
        lv_opa_t opa; /**< Opacity of whole image */
    } image;

    /**< Style of lines (not borders). */
    struct
    {
        lv_color_t color;
        lv_coord_t width;
        lv_opa_t opa;
        uint8_t rounded : 1; /**< 1: rounded line endings*/
    } line;
} lv_legacy_style_t;

/*************************
 *    GLOBAL VARIABLES
 *************************/
extern lv_legacy_style_t lv_style_scr;
extern lv_legacy_style_t lv_style_transp;
extern lv_legacy_style_t lv_style_transp_fit;
extern lv_legacy_style_t lv_style_transp_tight;
extern lv_legacy_style_t lv_style_plain;
extern lv_legacy_style_t lv_style_plain_color;
extern lv_legacy_style_t lv_style_pretty;
extern lv_legacy_style_t lv_style_pretty_color;
extern lv_legacy_style_t lv_style_btn_rel;
extern lv_legacy_style_t lv_style_btn_pr;
extern lv_legacy_style_t lv_style_btn_tgl_rel;
extern lv_legacy_style_t lv_style_btn_tgl_pr;
extern lv_legacy_style_t lv_style_btn_ina;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_legacy_style_init(void);

/**
 * Copy a style to an other
 * @param dest pointer to the destination style
 * @param src pointer to the source style
 */
void lv_legacy_style_copy(lv_legacy_style_t * dest, const lv_legacy_style_t * src);

/**
 * Mix two styles according to a given ratio
 * @param start start style
 * @param end end style
 * @param res store the result style here
 * @param ratio the ratio of mix [0..256]; 0: `start` style; 256: `end` style
 */
void lv_legacy_style_mix(const lv_legacy_style_t * start, const lv_legacy_style_t * end, lv_legacy_style_t * res, uint16_t ratio);

/**
 * Convert a legacy style to an `lv_style_t` that can be applied to objects.
 */
void lv_legacy_style_convert(lv_style_t *dest, lv_state_t state, const lv_legacy_style_t *src);

/**********************
 *      MACROS
 **********************/

/**
 * Create and initialize a `static` style
 * Example:
 *     LV_STYLE_CREATE(my_style, &lv_style_plain);
 *   is equivalent to
 *     static lv_legacy_style_t my_style;
 *     lv_style_copy(my_style, &lv_style_plain);
 *
 * If the style to copy is `NULL` `lv_style_plain` will be used.
 */
#define LV_LEGACY_STYLE_CREATE(name, copy_p) static lv_legacy_style_t name; lv_legacy_style_copy(&name, copy_p == NULL ? &lv_style_plain : copy_p);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_STYLE_COMPAT_H*/
