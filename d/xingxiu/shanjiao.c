// tianshan: /d/xingxiu/shanjiao.c
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��ɽ����");
        set("long", @LONG
��������ɽ���£��������Ǹ������Ƶ���ɽ��̧ͷ�������Կ�����ɽ
���ϵ������ѩ��һ����ɽ�������Ϊ���룬�������������ľ۾�����
�Ͻ��ǹ����ޱߵĴ��ԭ��������������ǣ�������ǽ�ͨҪ��ʱ����
�����ɵ��Ӱѹ����١�
LONG);
        set("exits", ([
            "north" : __DIR__"xxh",
            "east" : __DIR__"yili",
            "southeast" : __DIR__"silk9",
            "southwest" : "/d/hj/senlin1",
         ]));

        set("outdoors", "tianshan" );
        set("objects", ([
            __DIR__"npc/xxdizi3" : 1,
            __DIR__"npc/boshou"  : 1,          
         ]));

        set("coor/x",-310);
  set("coor/y",130);
   set("coor/z",0);
   set("coor/x",-310);
  set("coor/y",130);
   set("coor/z",0);
   set("coor/x",-310);
 set("coor/y",130);
   set("coor/z",0);
   setup();
}
#include "/d/xingxiu/job2.h";
