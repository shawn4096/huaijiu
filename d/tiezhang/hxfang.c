//hxfang.c ���᷿

inherit ROOM;

void create()
{
	set("short", "���᷿");
	set("long", @LONG
���Ǵ��������һ��С���䣬��ȻҲ����ʯ���ɣ������õķǳ����ʡ���
���ù�̺��ס����¶һ��ʯ�ڵĺۼ�������תȦ�ڷ���һЩ���ӣ��������ź�
�����棬����ȥһ�������ʡ������ǰ�����������ճ�����ĵط�������ͨ
���Ժ��
LONG
	);

	set("exits", ([ 
"north" : __DIR__"hhyuan-1",
"south" : __DIR__"wztang",
]));

	 set("objects", ([
__DIR__"npc/qqren" : 1,
__DIR__"npc/yahuan" : 1,
]));

        set("no_clean_up", 0);

	set("coor/x",-330);
  set("coor/y",-240);
   set("coor/z",10);
   setup();
}
