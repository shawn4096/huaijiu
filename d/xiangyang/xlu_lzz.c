// Room: xlu_lzz.c
// Looklove y2k/4/26

inherit ROOM;

void create()
{
        set("short","С·");
        set("long", @LONG
����ͨ���������һ��С·�����˲��Ǻܶࡣ·��ż���ܿ���������ѹ��
�ĺۼ���·���Գ����˵Ͱ��Ĺ�ľ�������ﲻʱ����һ������С�����������
�����������ˡ�
LONG
        );

        set("exits", ([
                "south" : __DIR__"xiaolu1",
                "north" : __DIR__"liuzz",
        ]));
 
        set("coor/x",-40);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}

