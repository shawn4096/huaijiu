// /d/city/wroad1.c

inherit ROOM;

void create()
{
	set("short", "��ʯ���");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ����������ҴҶ�����
����������밲�վ��ڡ�����ͨ�����ݳǡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"east" : __DIR__"ximen",
                "west" : __DIR__"wroad2",
                "northwest" : __DIR__"winmo",
	]));

   	set("coor/x",60);
  	set("coor/y",0);
   	set("coor/z",0);
   	setup();
}

void init()
{	
	object me=this_player();
	
	if ( me->query("family/family_name") == "ؤ��" 
	    && userp(me)
	    &&!me->query("gb/alloted")){
		if (me->query("family/master_name")== "�ɳ���"
		  ||me->query("family/master_name")== "�տն�"){
			me->set("gb/fenduo","���·ֶ�");
			me->set("gb/alloted",1);
			return;
		}
		if (me->query("family/master_name")== "�ⳤ��"
		  || me->query("family/master_name")== "������"){
			me->set("gb/fenduo","���ŷֶ�");
			me->set("gb/alloted",1);
			return;
		}
		if (me->query("family/master_name")== "������"){
			me->set("gb/fenduo","����");
			me->set("gb/alloted",1);
			return;
		}
		me->set("gb/fenduo","���·ֶ�");
		me->set("gb/alloted",1);
		return;
	}
}		
