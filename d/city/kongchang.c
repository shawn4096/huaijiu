// /d/city/kongchang

inherit ROOM;
#include <guanfu.h>

void create()
{
        set("short", "�㳡");
        set("long", @LONG
����֪���Աߵ�һƬС�ճ����ڶ��ߵ�ǽ�����˼��Źٸ�����׽��
��͢Ҫ���ĸ�ʾ (wanted list)������Χ������࿴���ֵ��ˣ����в�
��һЩ���ָ��֣�����Ҫ׽�õ�Ҫ���������֣������������Ұ�(jie)�� 
��Ҳ�в������ֺ���֮����һ��ԾԾ���ԡ�
LONG
        );

        set("item_desc", ([
                "wanted list" : (: GF_WANTED->look_wanted() :),
        ]));

        set("exits", ([
                "southwest" : "/d/city/guangchangbei",
        ]));

   	setup();
        call_out( (:call_other:), 1, GF_WANTED, "???");
}

void init()
{
        if( this_player()->query_condition("killer") )
                return;
        add_action("do_jie", ({"xian","jie"}));
}

int do_jie(string arg)
{
        return GF_WANTED->do_jie(arg);
}
