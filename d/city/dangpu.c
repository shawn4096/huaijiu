// Room: /d/city/dangpu.c
#include <ansi.h>;

inherit ROOM;

mapping *special=({
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
});

void getspec();

void create()
{
	set("short", "����");
	set("long", 
"����һ������������ƽ���Ƶ����ֺŵ��̣�һ���ĳ߸ߵĹ�̨���������\n"+
"ǰ����̨�ϰ���һ������(paizi)�� ��̨�����ŵ��̵��ϰ壬һ˫���������\n"+
"���������´������㣬��˵�������ڴ���������"+HBGRN+HIG+"�������׵�"+NOR+"����\n"
	);
        set("no_fight",1);
	set("no_sleep_room",1);

	set("item_desc", ([
		"paizi" : "��ƽ���ף��������ۡ�\n",
	]));
	set("objects", ([
		__DIR__"npc/huang" : 1,
	]));
	set("exits", ([
         "north" : __DIR__"guangchangnan",
	]));

	set("coor/x",110);
        set("coor/y",-30);
        set("coor/z",0);
	getspec();
        setup();
}

void init()
{
	add_action( "do_exchange", "exchange" );
	add_action( "do_exchange", "duihuan" );
	add_action( "do_look", "look" );
}

void getspec()
{
	mixed *file;
	int i;
	object ob;
	string tpw;
	
	file = get_dir("/clone/spec/");

	if( !sizeof(file) ) return notify_fail("�Ҳ����κ���Ʒ \n");
	for( i = 0; i < sizeof(file); i++ )
	{	tpw = "";
                file[i] = "/clone/spec/" + file[i];
                if( file_size(file[i]) < 0 ) continue;
		ob = new(file[i]);
		
		if(!objectp(ob)) continue;		
		if(!ob->query("credit")){
			//must dest
			destruct(ob);	
			 continue;
		}
		
		if (!ob->query("rest"))
			tpw = "��";		
		else
			tpw = "ÿ��"+chinese_number(ob->query("rest"))+"��";	
		special[i]=([
			"value"		:	ob->query("credit"),
			"name"		:	ob->query("name"),
			"id"		:	ob->query("id"),	
			"desc"		:	ob->query("desc"),	
			"degree"	:	ob->query("degree"),
			"tpw"		:	tpw, 
			"file"		:	file[i]
			 ]);
		destruct(ob);	
	}
}


int do_look(string arg) 
{       
	object me = this_player();
	int i;
        
	if(me->is_busy()) 
		return notify_fail("����æ���ء�\n");
        	
 
        if (arg == "paizi" ){   
	        write(query("special"));
	        write("��ƽ���ף��������ۡ�\n");
	        write("�����������ɡ��������׵㡱�����ø������׵�һ������Ƽ��������£�\n");
	        write("��������������������������������������������������������������������������������������������������������\n");
	        write(sprintf("�� %-25s  %-40s  %-10s %-12s %-6s��\n", "��������","��������","���ô���","ʹ������","����" ));
	        write("�ǩ�����������������������������������������������������������������������������������������������������\n");
	        for (i=0;i<sizeof(special);i++) {
	        	 if (!special[i]["value"]) continue;
	        	 write(sprintf("�� %-25s  %-41s %-10s %-12s "+HIY+"%-6d"+NOR+"��\n", special[i]["name"]+"("+special[i]["id"]+")",special[i]["desc"],chinese_number(special[i]["degree"])+"��",special[i]["tpw"],special[i]["value"] ));
	        }
	        write("��������������������������������������������������������������������������������������������������������\n");
	        write("��ʹ�ã�duihuan xxxx��ָ�����һ���á�\n");
		return 1;
	}     
	return 0;
}

int do_exchange(string arg) 
{
	int i,j;
	object ob,me = this_player();
	
	if(me->is_busy()) 
		return notify_fail("����æ���ء�\n");
  		
	if(!arg)
		return notify_fail("����һ�ʲô��\n"); 
  		
	for (i=0;i<sizeof(special);i++)
	if (arg == special[i]["id"])  
		j=i+1;	
	if(!j)
		return notify_fail("����û������һ�������\n");
        
        if (special[j-1]["value"]>me->query("sj_credit"))
		return notify_fail("�Բ��������еĸ������������һ�"+special[j-1]["name"]+"��\n");
        
	ob = new(special[j-1]["file"]);
	if(!objectp(ob))
		{return notify_fail("ϵͳ��������ϵWIZ��\n");}
		
	me->add("sj_credit",-special[j-1]["value"]);
	me->add("sj_credit_used",special[j-1]["value"]);
	ob->move(me,1);    
	message_vision(sprintf("�����ϰ�ߺ��һ������%s�һ����Ƽ�����%s������%s���������׵㡣��\n",me->query("name"),special[j-1]["name"],chinese_number(special[j-1]["value"])),me);
	tell_object(me,"��Ŀǰ��ʣ"
		+ chinese_number(me->query("sj_credit"))+"���������׵㣬���Ѿ��ۼ�ʹ����" 
		+ chinese_number(me->query("sj_credit_used")) +"���������׵㡣\n");
	log_file( "static/CREDIT",sprintf("%s(%s) | ����%s | ʣ:%s | ��:%s | �ۼ�:%s.\n", me->name(), me->query("id"), special[j-1]["name"],chinese_number(me->query("sj_credit")),chinese_number(special[j-1]["value"]),chinese_number(me->query("sj_credit_used"))));
        me->start_busy(1);
		
	return 1; 
}