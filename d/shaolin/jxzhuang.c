// Room: /d/shaolin/jxzhuang.c

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIY"����ׯ"NOR);
        set("long", @LONG
���ߵ�һ����լ��Ժ���ſڣ����ſ��ţ���ǰ����������ʯʨ�ӣ����弶
��ʯ̨���������ȶ���ͭ���Ĵ��š����ó�������һ���˼ҵ�ס�����ſ���
���������һ��ڵ׽��ֵĴ��ҡ�����ׯ����
LONG
        );
        set("exits", ([
              "west" : __DIR__"yidao2",
        ]));

        set("objects",([
                __DIR__"npc/youju" : 1,
                __DIR__"npc/youji" : 1,
        ]));
 
        set("coor/x",110);
  set("coor/y",80);
   set("coor/z",0);
   set("coor/x",110);
  set("coor/y",80);
   set("coor/z",0);
   setup();
}
