// /d/jiaxing/luzhang.c ½��ׯ
// by shang 97/6

inherit ROOM;

void create()
{
        set("short", "½��ׯ");
	set("long", @LONG
���Ǽ���һ�������Ĳ�ׯ, ½��ׯ��ԭׯ��½չԪ�򲡲��ζ���, ��
�޵���㼴����ѳ��½չԪ��������򸾵�������춽���������½��ׯ
����ͷ�����������������˵���С��ġ����ڵ��ҵ���½չԪ֮��½������
LONG
	);

	set("exits", ([
                "enter" : __DIR__"tianjing",
                "north" : __DIR__"shulin1",
	]));

        set("outdoors", "����");
	set("coor/x",150);
  set("coor/y",-340);
   set("coor/z",0);
   setup();
}

