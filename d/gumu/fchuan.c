// Room: /u/xdd/gumu/fanchuan.c
// Modify By River 98/08
inherit ROOM;
#include <ansi.h>
void create()
{
     set("short",HIY"����"NOR);
     set("long", @LONG
�˴����Ƿ�������������ɽ�����ڣ����������󽫾�������ʳ���ڴˣ���
����������;���ͻ��ƣ��ɰ�ɭӳ,ˮ������������䣬��Ȼ�н��Ͼ�ɫ��
LONG        );

     set("outdoors","��Ĺ");

     set("exits", ([
         "east" : "/d/xiangyang/shanxiroad1",
         "west" : __DIR__"xiaolu1",
     ]));

     set("coor/x",0);
  set("coor/y",40);
   set("coor/z",0);
   setup();
}

void init()
{       
        object me;
        int lvl;
        mapping learned;
        me = this_player();
        lvl = me->query_skill("xiaohun-zhang", 1);
        learned = me->query_learned();
        me->delete_skill("xiaohun-zhang");
        if (lvl > 0){
                me->delete_skill("anran-zhang");
                me->set_skill("anran-zhang", lvl);
                if (mapp(learned) && learned["xiaohun-zhang"] > 0)
                        me->improve_skill("anran-zhang",
                                learned["xiaohun-zhang"], 1);
                write(HIG "ϵͳ�ѽ����ġ������ơ�ת��Ϊ����Ȼ�����ơ���\n" NOR);
         }
        if(me->query_skill_mapped("strike") == "xiaohun-zhang")
            me->map_skill("strike", "anran-zhang");
        if(me->query_skill_mapped("parry") == "xiaohun-zhang")
            me->map_skill("parry", "anran-zhang");
        if(me->query_skill_prepared("strike") == "xiaohun-zhang")
            me->prepare_skill("strike","anran-zhang");
}
