// /d/wudang/shijie2.c ʯ��
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
������һ����ʵ��ʯ���ϣ���ʱ�������˻����ʹ���������
����һ�������£�һ�����ͱڣ�̧ͷ��Լ�ɼ�ɽ���Ƶ������壬ɽ
����棬���������������Ŀ�����������ǰ��һ��Ƭ���֡�
LONG
        );
        set("exits", ([
                "southup" : __DIR__"sldadao",
                "northdown" :__DIR__"shijie1",
        ]));

        set("objects",([
                __DIR__"npc/jingxiangke" : 2,

        ]));
        
        set("coor/x",20);
  set("coor/y",10);
   set("coor/z",20);
   setup();

}
