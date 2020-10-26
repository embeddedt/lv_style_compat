# lv_style_compat

`lv_style_compat` is a simple external module for LittlevGL 7, designed to help users of 6.x migrate to the new style system.

Note that:

* There may be certain style combinations which don't work like they did in 6.x.
* Using `lv_style_compat` will hinder your ability to make use of the new style optimizations that LittlevGL 7 has. What this means in practical terms is that using a "legacy" style with this module will likely consume more memory than rewriting the code in question to use v7 styles.

## Example


```c
lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);

static lv_style_t style;
lv_style_init(&style);

static lv_legacy_style_t v6_style;

lv_legacy_style_init();
lv_legacy_style_convert(&style, LV_STATE_DEFAULT, &v6_style);
lv_legacy_style_convert(&style, LV_STATE_DEFAULT, &lv_style_btn_rel);
lv_legacy_style_convert(&style, LV_STATE_PRESSED, &lv_style_btn_pr);
lv_legacy_style_convert(&style, LV_STATE_CHECKED, &lv_style_btn_tgl_rel);
lv_legacy_style_convert(&style, LV_STATE_CHECKED | LV_STATE_PRESSED, &lv_style_btn_tgl_pr);

lv_obj_add_style(btn, LV_BTN_PART_MAIN, &style);
lv_btn_set_checkable(btn, true);

lv_obj_t * label = lv_label_create(btn, NULL);
lv_label_set_text(label, "Button");

lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, 0);
```

## API description

Because LittlevGL 7 has reused the type name `lv_style_t` for the new style system, the classic styles now use the type name
`lv_legacy_style_t`.

The APIs have also been updated to match. For example, `lv_legacy_style_copy` can be used to copy one legacy style to another.

`lv_legacy_style_convert` can be used to convert a legacy style into a new one.

## Bug reporting

Please open an issue on this repository if a legacy style doesn't convert the way you expected.
