// Room: /dali/dongjie6.c
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
�����ڶ�����ϣ��ֵ��ϻ��ݺ���ľ�����дУ��������󣬽����������
��Ĳ�ɫʯ���̳ɣ��������̣�ɷ�Ǻÿ������ھ������ᷱ�ӣ�ϰ�׸��죬��
ʳ�����޲�������ԭ�������Ǹ��軨԰��Ʒ�ַ��ࡣ
LONG
	);
        set("outdoors", "����");
	set("exits", ([
           "east" : __DIR__"chahuayuan",
           "south" : __DIR__"dongjie7",
           "north" : __DIR__"dongjie5",
	]));

	set("coor/x",-290);
  set("coor/y",-440);
   set("coor/z",-20);
   set("coor/x",-290);
  set("coor/y",-440);
   set("coor/z",-20);
   setup();
}

