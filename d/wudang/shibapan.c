// /d/wudang/shibapan.c ʮ����
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","ʮ����");
        set("long", @LONG
��������һ���ܴ��б�£��׳�ʮ���̣���ʯ��һ��һ����ֱ��
�ϣ��ķѽ����������м���ɽ�񿪵�С�꣬�ο͵�������СϢ������
������ǰʮ��֮�����䵱�ص���������
LONG
        );
        set("exits", ([
                "westup" : __DIR__"shijie3",
                "northdown" :__DIR__"caihong",
        ]));

        set("coor/x",0);
  set("coor/y",-40);
   set("coor/z",60);
   setup();

}
