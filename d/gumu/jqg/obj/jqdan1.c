// jqdan1.c 绝情丹
// By Ilovemin 2016.5.3
#include <ansi.h>
inherit ITEM;

void create()
{
       set_name(HIG"断肠绝情丹"NOR, ({"duanqing dan"}));
       set_weight(500);
       if (clonep())
             set_default_object(__FILE__);
       else {
             set("unit", "枚");
             set("long","这是一枚四四方方骰子般的丹药，色作深黑，腥臭刺鼻。\n");
             set("value", 1000);
             set("unique", 1);
             set("no_give", 1);
             set("no_drop", 1);
             set("no_get", 1);
             }
             setup();
}
