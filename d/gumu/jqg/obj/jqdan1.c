// jqdan1.c ���鵤
// By Ilovemin 2016.5.3
#include <ansi.h>
inherit ITEM;

void create()
{
       set_name(HIG"�ϳ����鵤"NOR, ({"duanqing dan"}));
       set_weight(500);
       if (clonep())
             set_default_object(__FILE__);
       else {
             set("unit", "ö");
             set("long","����һö���ķ������Ӱ�ĵ�ҩ��ɫ����ڣ��ȳ��̱ǡ�\n");
             set("value", 1000);
             set("unique", 1);
             set("no_give", 1);
             set("no_drop", 1);
             set("no_get", 1);
             }
             setup();
}
