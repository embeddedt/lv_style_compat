/**
 * @file lv_style_compat.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "lv_style_compat.h"


/*********************
 *      DEFINES
 *********************/
#define STYLE_MIX_MAX 256
#define STYLE_MIX_SHIFT 8 /*log2(STYLE_MIX_MAX)*/

#define VAL_PROP(v1, v2, r) v1 + (((v2 - v1) * r) >> STYLE_MIX_SHIFT)
#define STYLE_ATTR_MIX(attr, r)                                                                                        \
    if(start->attr != end->attr) {                                                                                     \
        res->attr = VAL_PROP(start->attr, end->attr, r);                                                               \
    } else {                                                                                                           \
        res->attr = start->attr;                                                                                       \
    }

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
lv_legacy_style_t lv_style_scr;
lv_legacy_style_t lv_style_transp;
lv_legacy_style_t lv_style_transp_fit;
lv_legacy_style_t lv_style_transp_tight;
lv_legacy_style_t lv_style_plain;
lv_legacy_style_t lv_style_plain_color;
lv_legacy_style_t lv_style_pretty;
lv_legacy_style_t lv_style_pretty_color;
lv_legacy_style_t lv_style_btn_rel;
lv_legacy_style_t lv_style_btn_pr;
lv_legacy_style_t lv_style_btn_tgl_rel;
lv_legacy_style_t lv_style_btn_tgl_pr;
lv_legacy_style_t lv_style_btn_ina;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 *  Init the basic styles
 */
void lv_legacy_style_init(void)
{
    /* Not White/Black/Gray colors are created by HSV model with
     * HUE = 210*/

    /*Screen style*/
    lv_style_scr.glass               = 0;
    lv_style_scr.body.opa            = LV_OPA_COVER;
    lv_style_scr.body.main_color     = LV_COLOR_WHITE;
    lv_style_scr.body.grad_color     = LV_COLOR_WHITE;
    lv_style_scr.body.radius         = 0;
    lv_style_scr.body.padding.left   = 0;
    lv_style_scr.body.padding.right  = 0;
    lv_style_scr.body.padding.top    = 0;
    lv_style_scr.body.padding.bottom = 0;
    lv_style_scr.body.padding.inner  = LV_DPI / 20;

    lv_style_scr.body.border.color = LV_COLOR_BLACK;
    lv_style_scr.body.border.opa   = LV_OPA_COVER;
    lv_style_scr.body.border.width = 0;
    lv_style_scr.body.border.part  = LV_BORDER_FULL;

    lv_style_scr.body.shadow.color = LV_COLOR_GRAY;
    lv_style_scr.body.shadow.type  = LV_SHADOW_FULL;
    lv_style_scr.body.shadow.width = 0;

    lv_style_scr.text.opa          = LV_OPA_COVER;
    lv_style_scr.text.color        = lv_color_make(0x30, 0x30, 0x30);
    lv_style_scr.text.sel_color    = lv_color_make(0x55, 0x96, 0xd8);
    lv_style_scr.text.font         = LV_FONT_DEFAULT;
    lv_style_scr.text.letter_space = 0;
    lv_style_scr.text.line_space   = 2;

    lv_style_scr.image.opa     = LV_OPA_COVER;
    lv_style_scr.image.color   = lv_color_make(0x20, 0x20, 0x20);
    lv_style_scr.image.intense = LV_OPA_TRANSP;

    lv_style_scr.line.opa     = LV_OPA_COVER;
    lv_style_scr.line.color   = lv_color_make(0x20, 0x20, 0x20);
    lv_style_scr.line.width   = 2;
    lv_style_scr.line.rounded = 0;

    /*Plain style (by default near the same as the screen style)*/
    lv_legacy_style_copy(&lv_style_plain, &lv_style_scr);
    lv_style_plain.body.padding.left   = LV_DPI / 20;
    lv_style_plain.body.padding.right  = LV_DPI / 20;
    lv_style_plain.body.padding.top    = LV_DPI / 20;
    lv_style_plain.body.padding.bottom = LV_DPI / 20;

    /*Plain color style*/
    lv_legacy_style_copy(&lv_style_plain_color, &lv_style_plain);
    lv_style_plain_color.text.color      = lv_color_make(0xf0, 0xf0, 0xf0);
    lv_style_plain_color.image.color     = lv_color_make(0xf0, 0xf0, 0xf0);
    lv_style_plain_color.line.color      = lv_color_make(0xf0, 0xf0, 0xf0);
    lv_style_plain_color.body.main_color = lv_color_make(0x55, 0x96, 0xd8);
    lv_style_plain_color.body.grad_color = lv_style_plain_color.body.main_color;

    /*Pretty style */
    lv_legacy_style_copy(&lv_style_pretty, &lv_style_plain);
    lv_style_pretty.text.color        = lv_color_make(0x20, 0x20, 0x20);
    lv_style_pretty.image.color       = lv_color_make(0x20, 0x20, 0x20);
    lv_style_pretty.line.color        = lv_color_make(0x20, 0x20, 0x20);
    lv_style_pretty.body.main_color   = LV_COLOR_WHITE;
    lv_style_pretty.body.grad_color   = LV_COLOR_SILVER;
    lv_style_pretty.body.radius       = LV_DPI / 15;
    lv_style_pretty.body.border.color = lv_color_make(0x40, 0x40, 0x40);
    lv_style_pretty.body.border.width = LV_DPI / 50 >= 1 ? LV_DPI / 50 : 1;
    lv_style_pretty.body.border.opa   = LV_OPA_30;

    /*Pretty color style*/
    lv_legacy_style_copy(&lv_style_pretty_color, &lv_style_pretty);
    lv_style_pretty_color.text.color        = lv_color_make(0xe0, 0xe0, 0xe0);
    lv_style_pretty_color.image.color       = lv_color_make(0xe0, 0xe0, 0xe0);
    lv_style_pretty_color.line.color        = lv_color_make(0xc0, 0xc0, 0xc0);
    lv_style_pretty_color.body.main_color   = lv_color_make(0x6b, 0x9a, 0xc7);
    lv_style_pretty_color.body.grad_color   = lv_color_make(0x2b, 0x59, 0x8b);
    lv_style_pretty_color.body.border.color = lv_color_make(0x15, 0x2c, 0x42);

    /*Transparent style*/
    lv_legacy_style_copy(&lv_style_transp, &lv_style_plain);
    lv_style_transp.glass             = 1;
    lv_style_transp.body.border.width = 0;
    lv_style_transp.body.opa          = LV_OPA_TRANSP;

    /*Transparent fitting size*/
    lv_legacy_style_copy(&lv_style_transp_fit, &lv_style_transp);
    lv_style_transp_fit.body.padding.left   = 0;
    lv_style_transp_fit.body.padding.right  = 0;
    lv_style_transp_fit.body.padding.top    = 0;
    lv_style_transp_fit.body.padding.bottom = 0;

    /*Transparent tight style*/
    lv_legacy_style_copy(&lv_style_transp_tight, &lv_style_transp_fit);
    lv_style_transp_tight.body.padding.inner = 0;

    /*Button released style*/
    lv_legacy_style_copy(&lv_style_btn_rel, &lv_style_plain);
    lv_style_btn_rel.body.main_color     = lv_color_make(0x76, 0xa2, 0xd0);
    lv_style_btn_rel.body.grad_color     = lv_color_make(0x19, 0x3a, 0x5d);
    lv_style_btn_rel.body.radius         = LV_DPI / 15;
    lv_style_btn_rel.body.padding.left   = LV_DPI / 4;
    lv_style_btn_rel.body.padding.right  = LV_DPI / 4;
    lv_style_btn_rel.body.padding.top    = LV_DPI / 6;
    lv_style_btn_rel.body.padding.bottom = LV_DPI / 6;
    lv_style_btn_rel.body.padding.inner  = LV_DPI / 10;
    lv_style_btn_rel.body.border.color   = lv_color_make(0x0b, 0x19, 0x28);
    lv_style_btn_rel.body.border.width   = LV_DPI / 50 >= 1 ? LV_DPI / 50 : 1;
    lv_style_btn_rel.body.border.opa     = LV_OPA_70;
    lv_style_btn_rel.body.shadow.color   = LV_COLOR_GRAY;
    lv_style_btn_rel.body.shadow.width   = 0;
    lv_style_btn_rel.text.color          = lv_color_make(0xff, 0xff, 0xff);
    lv_style_btn_rel.image.color         = lv_color_make(0xff, 0xff, 0xff);

    /*Button pressed style*/
    lv_legacy_style_copy(&lv_style_btn_pr, &lv_style_btn_rel);
    lv_style_btn_pr.body.main_color = lv_color_make(0x33, 0x62, 0x94);
    lv_style_btn_pr.body.grad_color = lv_color_make(0x10, 0x26, 0x3c);
    lv_style_btn_pr.text.color      = lv_color_make(0xa4, 0xb5, 0xc6);
    lv_style_btn_pr.image.color     = lv_color_make(0xa4, 0xb5, 0xc6);
    lv_style_btn_pr.line.color      = lv_color_make(0xa4, 0xb5, 0xc6);

    /*Button toggle released style*/
    lv_legacy_style_copy(&lv_style_btn_tgl_rel, &lv_style_btn_rel);
    lv_style_btn_tgl_rel.body.main_color   = lv_color_make(0x0a, 0x11, 0x22);
    lv_style_btn_tgl_rel.body.grad_color   = lv_color_make(0x37, 0x62, 0x90);
    lv_style_btn_tgl_rel.body.border.color = lv_color_make(0x01, 0x07, 0x0d);
    lv_style_btn_tgl_rel.text.color        = lv_color_make(0xc8, 0xdd, 0xf4);
    lv_style_btn_tgl_rel.image.color       = lv_color_make(0xc8, 0xdd, 0xf4);
    lv_style_btn_tgl_rel.line.color        = lv_color_make(0xc8, 0xdd, 0xf4);

    /*Button toggle pressed style*/
    lv_legacy_style_copy(&lv_style_btn_tgl_pr, &lv_style_btn_tgl_rel);
    lv_style_btn_tgl_pr.body.main_color = lv_color_make(0x02, 0x14, 0x27);
    lv_style_btn_tgl_pr.body.grad_color = lv_color_make(0x2b, 0x4c, 0x70);
    lv_style_btn_tgl_pr.text.color      = lv_color_make(0xa4, 0xb5, 0xc6);
    lv_style_btn_tgl_pr.image.color     = lv_color_make(0xa4, 0xb5, 0xc6);
    lv_style_btn_tgl_pr.line.color      = lv_color_make(0xa4, 0xb5, 0xc6);

    /*Button inactive style*/
    lv_legacy_style_copy(&lv_style_btn_ina, &lv_style_btn_rel);
    lv_style_btn_ina.body.main_color   = lv_color_make(0xd8, 0xd8, 0xd8);
    lv_style_btn_ina.body.grad_color   = lv_color_make(0xd8, 0xd8, 0xd8);
    lv_style_btn_ina.body.border.color = lv_color_make(0x90, 0x90, 0x90);
    lv_style_btn_ina.text.color        = lv_color_make(0x70, 0x70, 0x70);
    lv_style_btn_ina.image.color       = lv_color_make(0x70, 0x70, 0x70);
    lv_style_btn_ina.line.color        = lv_color_make(0x70, 0x70, 0x70);
}

/**
 * Copy a style to an other
 * @param dest pointer to the destination style
 * @param src pointer to the source style
 */
void lv_legacy_style_copy(lv_legacy_style_t * dest, const lv_legacy_style_t * src)
{
    memcpy(dest, src, sizeof(lv_legacy_style_t));
}

/**
 * Mix two styles according to a given ratio
 * @param start start style
 * @param end end style
 * @param res store the result style here
 * @param ratio the ratio of mix [0..256]; 0: `start` style; 256: `end` style
 */
void lv_legacy_style_mix(const lv_legacy_style_t * start, const lv_legacy_style_t * end, lv_legacy_style_t * res, uint16_t ratio)
{
    STYLE_ATTR_MIX(body.opa, ratio);
    STYLE_ATTR_MIX(body.radius, ratio);
    STYLE_ATTR_MIX(body.border.width, ratio);
    STYLE_ATTR_MIX(body.border.opa, ratio);
    STYLE_ATTR_MIX(body.shadow.width, ratio);
    STYLE_ATTR_MIX(body.padding.left, ratio);
    STYLE_ATTR_MIX(body.padding.right, ratio);
    STYLE_ATTR_MIX(body.padding.top, ratio);
    STYLE_ATTR_MIX(body.padding.bottom, ratio);
    STYLE_ATTR_MIX(body.padding.inner, ratio);
    STYLE_ATTR_MIX(text.line_space, ratio);
    STYLE_ATTR_MIX(text.letter_space, ratio);
    STYLE_ATTR_MIX(text.opa, ratio);
    STYLE_ATTR_MIX(line.width, ratio);
    STYLE_ATTR_MIX(line.opa, ratio);
    STYLE_ATTR_MIX(image.intense, ratio);
    STYLE_ATTR_MIX(image.opa, ratio);

    lv_opa_t opa = ratio == STYLE_MIX_MAX ? LV_OPA_COVER : ratio;

    res->body.main_color   = lv_color_mix(end->body.main_color, start->body.main_color, opa);
    res->body.grad_color   = lv_color_mix(end->body.grad_color, start->body.grad_color, opa);
    res->body.border.color = lv_color_mix(end->body.border.color, start->body.border.color, opa);
    res->body.shadow.color = lv_color_mix(end->body.shadow.color, start->body.shadow.color, opa);
    res->text.color        = lv_color_mix(end->text.color, start->text.color, opa);
    res->image.color       = lv_color_mix(end->image.color, start->image.color, opa);
    res->line.color        = lv_color_mix(end->line.color, start->line.color, opa);

    if(ratio < (STYLE_MIX_MAX >> 1)) {
        res->body.border.part = start->body.border.part;
        res->glass            = start->glass;
        res->text.font        = start->text.font;
        res->body.shadow.type = start->body.shadow.type;
        res->line.rounded     = start->line.rounded;
    } else {
        res->body.border.part = end->body.border.part;
        res->glass            = end->glass;
        res->text.font        = end->text.font;
        res->body.shadow.type = end->body.shadow.type;
        res->line.rounded     = end->line.rounded;
    }
}

void lv_legacy_style_convert(lv_style_t *dest, lv_state_t state, const lv_legacy_style_t *src) {
    /* First set all the new options to behave like LittlevGL 6.x and below */
    lv_style_set_bg_grad_dir(dest, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_outline_width(dest, LV_STATE_DEFAULT, 0);
    lv_style_set_transition_time(dest, LV_STATE_DEFAULT, 0);
    lv_style_set_transition_delay(dest, LV_STATE_DEFAULT, 0);

    /* Set the 'body' properties */

    lv_style_set_radius(dest, state, src->body.radius);
    lv_style_set_pad_top(dest, state,src->body.padding.top);
    lv_style_set_pad_bottom(dest, state,src->body.padding.bottom);
    lv_style_set_pad_left(dest, state,src->body.padding.left);
    lv_style_set_pad_right(dest, state,src->body.padding.right);
    lv_style_set_pad_inner(dest, state,src->body.padding.inner);
    lv_style_set_bg_color(dest, state,src->body.main_color);
    lv_style_set_bg_grad_color(dest, state,src->body.grad_color);
    
    lv_style_set_bg_opa(dest, state,src->body.opa);
    lv_style_set_border_color(dest, state,src->body.border.color);
    lv_style_set_border_side(dest, state,src->body.border.part); /* XXX: relies on identical constants in v7.0 */
    lv_style_set_border_opa(dest, state,src->body.border.opa);
    lv_style_set_border_width(dest, state,src->body.border.width);
    lv_style_set_shadow_width(dest, state,src->body.shadow.width);
    lv_style_set_shadow_color(dest, state,src->body.shadow.color);
    /* FIXME: use shadow_ofs_y to implement lv_shadow_type_t */


    /* Set the 'text' properties */
    lv_style_set_text_letter_space(dest, state,src->text.letter_space);
    lv_style_set_text_line_space(dest, state,src->text.line_space);
    lv_style_set_text_color(dest, state,src->text.color);
    lv_style_set_text_sel_color(dest, state,src->text.sel_color);
    lv_style_set_text_opa(dest, state,src->text.opa);
    lv_style_set_text_font(dest, state,src->text.font);

    /* Set the 'value_str' properties for backwards compatibility */
    lv_style_set_value_letter_space(dest, state,src->text.letter_space);
    lv_style_set_value_line_space(dest, state,src->text.line_space);
    lv_style_set_value_color(dest, state,src->text.color);
    lv_style_set_value_opa(dest, state,src->text.opa);
    lv_style_set_value_font(dest, state,src->text.font);

    /* Set the 'line' properties */
    lv_style_set_line_width(dest, state,src->line.width);
    lv_style_set_line_color(dest, state,src->line.color);
    lv_style_set_line_rounded(dest, state,src->line.rounded);
    lv_style_set_line_opa(dest, state,src->line.opa);

    /* Set the 'image' properties */
    lv_style_set_image_recolor(dest, state,src->image.color);
    lv_style_set_image_recolor_opa(dest, state,src->image.intense);
    lv_style_set_image_opa(dest, state,src->image.opa);
}
