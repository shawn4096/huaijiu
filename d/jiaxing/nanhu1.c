// Room: /d/jiaxing/nanhu1.c

inherit ROOM;

void create()
{
	set("short", "�����Ϻ�");
	set("long", @LONG
�������̲������Ϻ������ϼ�ֻ�������ε������ϵ��οͺ�
��¥Ů������Ц����ˮ���û�д��Ƕɲ���ȥ�ġ�����֪��˭��
���׶���һЩľ׮��׮��Ǳ��ˮ��֮��һ����ĵط�����ʹ�ǲ���
�Ṧ��������ȥҲ����ˮ��Ư�����ӡ�
LONG
	);

	set("exits", ([
		"south" : __DIR__"yanyu",
                "northwest" : __DIR__ "nanhu",
	]));

	set("outdoors", "����");
	set("coor/x",160);
  set("coor/y",-310);
   set("coor/z",0);
   setup();
}

