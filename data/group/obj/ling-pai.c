#include <ansi.h>

inherit ITEM;

int save_room_file(string yn, string file, string str);
int do_mkroom (string file);
int init_var();
int save_file();
int do_saveroom(string arg);

mapping tmp = ([
  "no_fight"            :       0,
  "no_clean_up"         :       0,
  "valid_startroom"     :       0,
  "file_name"           :       "",
  "short"               :       "",
  "long"                :       "",
  "outdoors"            :       "",
  "g_name"				:		"",
  "hard"				:		"",
  "damage"				:		"",
  "combat_exp"			:		"",
  "skill_lvl"			:		"",
  "item_desc"           :       ([]),
  "exits"               :       ([]),
  "objects"             :       ([]),
]);

string *special_props = ({
        "short", "long", "file_name" });


void create()
{
    set_name(RED "����" NOR, ({ "ling pai", "pai" }) );
    set("long", "����ǰ���������������ơ�����������˻ٻ���Щ����(huiling)��\n"
    	+		"���ᱻ��Ϊ����������ˡ�Ϊ�˱�֤���Ƶİ��ȣ����ΰ�������ϣ��\n"
    	+		"��ϣ���ܹ���ļ������������������������(shouling)��\n" );
    set("unit","��");
    set("no_get", "������������̫�������˰ɣ�");
    set("no_drop", 1);
    set("no_put", 1);
    set("no_give", 1);      
    set("material", "wood");
    set_weight(1);
    setup();
}

void init()
{
	object me=this_player();
	object env = environment(this_player());
	
	if( me->query_condition("killer")
		 && me->query("g_name")+me->query("g_type") == env->query("g_name") )
	{
	    message_vision(HIY "$Nһ����̳��...ֻ��������ȣ���ͬը�װ��ڴ������졣"
            "$N��������������Ҳվ����ס����һ����ͨһ������������\n\n" NOR, me);
        message_vision(HIY "ֻ����һ����ȣ�$N��������ɱ��Խ����������Ϊ��"
            "���ڵ�����̳�������д�����ִ�����Ӻ��ڣ�\n\n" NOR, me);
        message_vision(HIR "ִ������һӿ���ϣ��Ұ����£�$Nʹ�û��˹�ȥ......\n" NOR, me);

        me->move("/data/group/zongtan");
        me->unconcious();
	}
	
	
    add_action("do_huiling", "huiling");
    add_action("do_shouling", "shouling");
}

int do_shouling()
{
    object me = this_player();
    object ob;
    object ob1 = environment(me);
	int lvl;

	if( !me->query( "g_level" ) )
		return notify_fail( "�㻹���Ƚ������Լ��İ�����˵�ɡ�\n" );
	if( me->query( "g_name" ) + me->query( "g_type" ) != ob1->query( "g_name" ) )
		return notify_fail( "��ô����������ˣ�\n" );
	if( me->query( "g_level" ) > 1 )
		return notify_fail( "ֻ�а���������ļ��̳������\n" );
	if( me->is_busy() )
		return notify_fail("��������æ���ء�\n");
	if( me->is_fighting() )
		return notify_fail("��ȴ������˵�ɡ�\n");
		
	if( me->query( "balance" ) < 2000000 )
		return notify_fail( "���Ѿ�û�в�����ļ�����ˡ�\n" );
		
	if( me->query( "combat_exp" ) * 3 / 2 < ob1->query( "combat_exp" ) )
		return notify_fail( "����Ŀǰ�Ĺ����������޷���ļ������������̳������\n" );

	message_vision( HIC"$N��ϧ�ķѾ��ʣ���Ҫ��ļ��λ�书���Ӹ�ǿ����̳������\n"NOR, me );
	
	me->add( "balance", -2000000 );
	me->start_busy( 2 );
	
	if( random(10) < 4 )
	{
		message_vision( HIC"���ź���$Nû���ҵ����ʵ���ѡ��\n"NOR, me );
	}
	else
	{
		message_vision( HIC"�ɹ��ˣ�$N�ҵ�����λ�µ���̳��������̳�ķ�����ǿ�ˡ�\n"NOR, me );
		ob1->add("combat_exp", 100000);
		ob1->add("hard",100);
		lvl=ob1->query("skill_lvl");
		if((lvl+10)*(lvl+10)*(lvl+10)<=ob1->query("combat_exp") * 10)
			ob1->add("skill_lvl",10);
	    if( (ob = present("hufa zhanglao", ob1) ) )
	    	destruct(ob);
	    if( (ob = present("hufa zhanglao", ob1) ) )
	    	destruct(ob);
	    call_out("newhufa",1,ob1);
		do_saveroom("");
	}

	return 1;

}

int newhufa(object ob1)
{
	    new("/data/group/npc/hufa.c")->move(ob1);
	    new("/data/group/npc/hufa.c")->move(ob1);
}

int do_huiling()
{
    object me = this_player();
    object ob;
    object ob1 = environment(me);
    int i;
    
	if( me->is_busy() )
		return notify_fail("��������æ���ء�\n");
	if( me->is_fighting() )
		return notify_fail("��ȴ������˵�ɡ�\n");
	if( me->query("g_name") + me->query("g_type") == ob1->query("g_name") )
		return notify_fail("��û�и��ɣ�\n");
		    
    message_vision( HIR"$N��Цһ��������ǰȥ������һ�ţ���������������\n"NOR,me);
    
    ob1->add("damage",1);
    if( ob1->query("damage") < 200 )
    {
    	message_vision( HIC"\n������������һ�������˵Ľ�ӡ��\n"NOR,me );
    }
    else if( ob1->query("damage") < 500 )
    {
    	message_vision( HIC"\n��������ػζ��˼��¡�\n"NOR,me );
    }
    else if( ob1->query("damage") < 1000 )
    {
    	message_vision( HIC"\n�������ҵ�ǰ��ζ�������\n"NOR,me );
    }
    else
    {
    	message_vision( HIR"\n����ҡҡ��׹���ۿ���Ҫ�����ˡ�\n"NOR,me );
    }
    
    if( ob1->query("damage") >= ob1->query("hard") )
    {
    	message_vision( HIY"\nֻ����һ�����죬ǰ���������������Ʊ��˵����ˡ�\n"NOR,me );
	    message("channel:chat", HIC "���������š���" HIR + ob1->query("g_name")
	    	+ HIG "��̳" HIC + "�������ˡ�\n" NOR,users());
	    message("channel:chat", HIC "���������š���" HIR + ob1->query("g_name")
	    	+ HIC "���Ļ�ɢ�����Ƚ�ɢ��\n" NOR,users());
write_file("/log/group",sprintf("%s %s ��ɢ��ԭ����̳�����١�\n",ctime(time())[4..19],ob1->query("g_name")));
		ob1->set("short", HIR "" + ob1->query("g_name") + HIG "��̳����" NOR );
		ob1->set("long", "����������" + ob1->query("g_name") + "����̳�����������Ѿ������˵����ˡ�\n");
		ob1->delete("combat_exp");
		ob1->delete("skill_lvl");
		ob1->delete("g_name");
		ob1->delete("damage");
		ob1->delete("hard");
		ob1->delete("objects");		
do_saveroom("");

	    if( (ob = present("hufa zhanglao", ob1) ) )
	    	destruct(ob);
	    if( (ob = present("hufa zhanglao", ob1) ) )
	    	destruct(ob);
	    if( (ob = present("ling pai", ob1) ) )
	    	destruct(ob);
	    	

    	return 1;
    }

	me->start_busy( 4 );
        
    i = 1;
    while( (ob = present("hufa zhanglao "+sprintf("%d",i), ob1) ) )
    {
    	ob->kill_ob(me);
    	i++;
	}
        
    return 1;
}



int save_room_file(string yn, string file, string str)
{
	if( strlen(yn)<1 || yn[0]!='y' )
		return 1;

	if ( write_file(file, str, 1) ) 
	{
	    return 1;
	}
	else 
	{
	    write ("Mudos ����д��("+file+")ʧ��!!\n");
		return 0;
	}
}

int init_var ()
{
	tmp["no_fight"]               =       0;
	tmp["no_clean_up"]            =       0;
	tmp["valid_startroom"]        =       0;
	tmp["file_name"]              =       "";
	tmp["short"]                  =       "";
	tmp["long"]                   =       "";
	tmp["outdoors"]               =       "";
	tmp["g_name"]					=		"";
	tmp["hard"]					=		"";
	tmp["damage"]					=		"";
	tmp["combat_exp"]				=		"";
	tmp["skill_lvl"]				=		"";
	tmp["item_desc"]              =       ([]);
	tmp["exits"]                  =       ([]);
	tmp["objects"]                =       ([]);
}


int do_saveroom(string arg)
{
        object env;
        string str, *name, file, pre, suc;
        mapping prop;
        int i;

        env = environment(this_player());
        file = file_name(env) + ".c";

        if (file_size(file) <= 0) return
          notify_fail ("û���ⷿ��ĵ���: "+file+"\n");

        name = explode (read_file (file), "\n");
        pre = "";
        for (i=0; i<sizeof (name); i++)
          if (strsrch (name[i], "void create") != 0)
            pre += name[i] + "\n";
          else break;
        pre += "void create ()\n{\n";

        i += 2;
        while (name && name[i][0..0] != "}") i++;
        suc = ""; i++;
        while (i<sizeof(name)) suc += name[i++]+"\n";

        prop = env->query_entire_dbase();

        str = pre;
        str = sprintf ("%s  set (\"short\", \"%s\");\n"
               "  set (\"long\", @LONG\n%sLONG);\n\n",
             str, prop["short"], prop["long"]);

        name = keys(prop);
        for(i=0; i<sizeof(name); i++) {
          if( member_array(name[i], special_props)!=-1 ) continue;
          if ( (intp(prop[name[i]]) && prop[name[i]]>0) ||
                (stringp(prop[name[i]]) && prop[name[i]] != "" ) ||
                (mapp(prop[name[i]]) && prop[name[i]] == ([])) ||
                sizeof (prop[name[i]]) > 0)
                    str += sprintf("  set(\"%s\", %O);\n",
                                   name[i], prop[name[i]] );
        }
        if (sizeof (suc) < 5)
         str += "\n  setup();\n}\n";
        else
         str += "\n  setup();\n}\n"+suc;

        return save_room_file("y", file, str);
}
