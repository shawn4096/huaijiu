// zhongtang.c

inherit ROOM;
#include <ansi.h>

void create()
{
       set("short",HIC"����"NOR);
       set("long", @LONG
��ٲ�����һ��é�ݵ����ã�ֻ�����г����ª�����ྻ�쳣������ֻ��
һ��һ����������ޱ��
LONG
        );

       set("exits", ([
          "out" : __DIR__"xiaolu",
          "east" : __DIR__"xiaoshi",
          "north" : __DIR__"wshi",
       ]));     
       setup();
}

void init()
{
       object me = this_player();
       if( me->query("family/family_name") =="��Ĺ��"
       && !me->query("gumu/buchang")
       && me->query_skill("strike", 1) > me->query_skill("hand", 1)){
          me->set_skill("hand", me->query_skill("strike", 1));
          me->set("gumu/buchang", 1);
          tell_object(me,HIG"ϵͳ�Զ�����ġ������ַ����ȼ������ɡ������Ʒ����ĵȼ���\n"NOR);
       }
}
