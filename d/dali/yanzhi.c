// Modify By River 98/12/
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short",HIR"��֬���۵�"NOR);
        set("long", @LONG
�����м����һֻ��ƿ��������˼�֧�����������ǽ����������һЩ
ֽ�����ұ�ǽ�Ϲ��ż�ֻС�������������Щ���ۣ�������һֻ���Ů����
��Ц�����ؽӴ����ˡ�
LONG
);
        set("exits", ([ 
              "east" : __DIR__"xijie7",
	]));

        set("objects", ([
              __DIR__"npc/nvdianzhu" : 1
        ]));
        set("coor/x",-340);
  set("coor/y",-450);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/yanzhi",1);
      }
}
