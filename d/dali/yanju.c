inherit ROOM;

void create()
{
	set("short", "�����ξ�");
	set("long", @LONG
����һ���ṹ��ΰ�Ľ���������ʯ̳�ϸ�����һ�����ɶ�ߵ���ˣ�����
����Ʈ�������ʢ�����Σ���������в��ٶ�������ԭ���ٸ�Ϊ�˱��ڹ�
��, ������˰, ��������ξ�, ֱ�������ڳ�͢����ڴ���Щ������˵Ц��
LONG
	);

	set("exits", ([
                "west" : __DIR__"beijie5",
	]));

	set("objects", ([
	        __DIR__"npc/yanshang" : 2,
	]));

	set("coor/x",-280);
  set("coor/y",-380);
   set("coor/z",-20);
   set("coor/x",-280);
  set("coor/y",-380);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/yanju",1);
      }
}
