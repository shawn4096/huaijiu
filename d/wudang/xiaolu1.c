// xiaolu1.c �ּ�С��
// by shang 97/6

inherit ROOM;

void create()
{
	set("short", "�ּ�С��");
	set("long", @LONG
������һ��С���ϣ��������������ӣ�����ɭɭ���������أ���
����Ҷ��������������������Ķ������������������ȡ�
LONG
	);

	set("exits", ([
                "east" : __DIR__"donglang2",
                "west" : __DIR__"xilang1",
                "south" : __DIR__"xiaolu2",
                "north" : __DIR__"sanqingdian",
	]));
        set("objects",([
                "/kungfu/class/wudang/wanqing" : 1,
//       "/u/dubei/npc/weitian" : 1,
//        "/clone/npc/zhangzz" : 1,
        ]));

	set("coor/x",-20);
  set("coor/y",-80);
   set("coor/z",100);
   setup();
}

