#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"��ͼ"NOR, ({ "he tu","he","tu" }));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("no_steal",1);
                set("no_drop",1);
                set("treasure",1);
                set("unique",1);
                set("material", "paper");
                set("skill", ([
                        "name": "qimen-bagua",  
                        "jing_cost":    40,     
                        "difficulty":   20,     
                        "max_skill":    120,
                ]) );
        }
}


