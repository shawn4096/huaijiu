// natured.c
// added reclaim and unique find. by snowman 28/10/1999
// optimized by Yuj 19991112

#include <ansi.h>

#define TIME_TICK (time()*60)
#define ANTIROBOT "/clone/npc/antirobot"
#define CALLOUT_TICK 30
#define DECLARE_FILE "/data/declare.txt"

nosave int current_day_phase, current_month;
mapping *day_phase;
string daytime = "";

string *month_time = ({
	"�������ĵ������ˣ�",
	"��������ط���������ӣ�",
	"�����𽥱�ů�ˣ�",
	"�Ѿ��ǳ���ʱ���ˣ�",
	"֪�˵Ľ�������о�����ʢ�ĵ���Ϣ��",
	"������÷ǳ����ȣ�",
	"��Ȼ�������ˣ�����������Щ�ȣ�",
	"����ѽڿ쵽�ˣ�",
	"һ����紵���������˵��ϵ���Ҷ��",
	"��ȥ������",
	"����������",
	"�쵽����ˣ�",
});
string *month_desc = ({
	"����һ��������",
	"����һ���紺���µ�",
	"����һ���������µ�",
	"����һ�����ĵ�",
	"����һ��ʢ�ĵ�",
	"����һ�����ĵ�",
	"����һ�������",
	"����һ�����յ�",
	"����һ�������",
	"����һ��������",
	"����һ��¡����",
	"����һ��������",
});

mapping *read_table(string file);
void init_day_phase();

void create()
{
	day_phase = read_table("/adm/etc/nature/day_phase");
	init_day_phase();
}

void init_day_phase()
{
	mixed *local;
	int i, t;

	// Get minutes of today.
	local = localtime(TIME_TICK);
	t = local[2] * 60 + local[1];
	current_month = local[4];

	// Find the day phase for now.
	for( i=0; i < sizeof(day_phase); i++)
		if( t >= day_phase[i]["length"] )
			t -= (int)day_phase[i]["length"];
		else break;

	current_day_phase = i;
	daytime = day_phase[current_day_phase]["event_fun"];

	// MUD ����ʱ����ˣ�ʱ�����ƫ������ǵ�������ÿСʱִ��һ��
	
	i = time();
	
	// Modify by Yu Jue 98-8-20
	remove_call_out("init_day_phase");
	call_out("init_day_phase", 3600 - i % 3600);
	
	
	// check reboot
	//�ĳ�ÿ��7������һ�� by renlai
	
	local = localtime(i);
     //local[6] == 1 &&	
	if (uptime() > 7*3600*24) {
		if (local[2] < 8) {
			if (find_call_out("update_day_phase") != -1) return; message("channel","\n\t"+"����վ���ڱ���ʱ��˵����ŵ�֮���Զ�����������\n\n", users());
		} 
		else if (local[2] < 13) "/cmds/common/reboot"->main(this_object(), "10");
	}
	
	
	

	// Since in our time scale, 1 minute == 1 second in RL, so we don't need
	// any conversion before using this number as call_out dalay, if you 
	// changed the time scale, be sure to convert it.
	remove_call_out("update_day_phase");
	call_out("update_day_phase",
		(int)day_phase[current_day_phase]["length"] - t);
	remove_call_out("test_robot");
	call_out("test_robot", 20+random(CALLOUT_TICK));
	remove_call_out("find_unique");
	call_out("find_unique", 60+random(CALLOUT_TICK));
	// ����Ƶ������ʱ������Ϣ
//	remove_call_out("declare_channel");
//	call_out("declare_channel",1200);
}

void declare_channel()
{
	string s_declare,txt;
	int line=1,i,totle=0,j,k;
	mapping *obj=({ });

	call_out("declare_channel",1200);

	while( s_declare = read_file(DECLARE_FILE,line,1) ) {
		if( sscanf( s_declare, "�ı���%sȨֵ��%d",	txt,i ) == 2 ) {
			obj += ({ (["txt": txt, "weight": i]) });
			totle += i;
		}
		
		line ++;
	}

	if( totle == 0 ) return;
	j=random(totle)+1;
	i=0;k=0;
	while(i+obj[k]["weight"]<j) {
		i+=obj[k]["weight"];
		k++;
	}
	message("channel:declare", HIY "\n����Ϣ��"+ obj[k]["txt"]+"\n" NOR,users());
	return;
}

string query_daytime(){ return daytime; }

int is_night()
{
	switch(daytime){
		case "event_night":
		case "event_midnight": 
			return 1;
		default: return 0;
	}
}

void update_day_phase()
{
	current_day_phase = (++current_day_phase) % sizeof(day_phase);
	if( !undefinedp(day_phase[current_day_phase]["event_fun"]) )
		call_other(this_object(), day_phase[current_day_phase]["event_fun"]);
	message("outdoor:vision", day_phase[current_day_phase]["time_msg"] + "\n" NOR, users());
	daytime = day_phase[current_day_phase]["event_fun"];
	remove_call_out("update_day_phase");
	call_out("update_day_phase", day_phase[current_day_phase]["length"]);

}

string ppl;

void test_robot()
{
	object *obs = filter_array(users(), (: environment :)), ob, robot;
	int i = sizeof(obs), j = 10, count;
	string *arg;

	remove_call_out("test_robot");
	call_out("test_robot", CALLOUT_TICK/2+random(CALLOUT_TICK));
	if (i < 1) return;
	count = uptime();
	while (j--) {
		ob = obs[random(i)];
		if (wiz_level(ob)) continue;
		if (ob->query_condition("killer")) continue;
		if (ob->is_ghost()) continue;
		if (query_idle(ob) > 30) continue;
		if (ob->is_fighting()) continue;
		if (ob->query("id") == ppl) continue;
		if (in_input(ob)) continue;
		if (ob->query("combat_exp") < 3000) continue;
		if (ob->query("combat_exp") < 100000 && count - ob->query_temp("robottest") < 3600) continue;
		if (ob->query("combat_exp") >= 100000 && count - ob->query_temp("robottest") < 1800) continue;
		arg = explode(base_name(environment(ob)), "/");
		if (arg[0] == "u") continue;
		if (arg[1] == "wizard") continue;
		if (arg[1] == "death") continue;
		break;
	}
	if (j < 0) return;
	ppl = ob->query("id");
	ob->set_temp("robottest", count);
	count = 3+random(2);
	robot = new(ANTIROBOT+count);
	CHANNEL_D->do_channel( robot, "sys", ob->name(1)+"("+capitalize(ppl)+")���ڽ��ܻ����� "+count+" �ĳ�顣");
	robot->test_robot(ob);
}

int filtdata(object ob)
{
	reset_eval_cost();
	if (!clonep(ob) || ob->is_character() || !ob->query("unique") || !environment(ob))
		return 0;
	return 1;
}

void find_unique() // Reclaim and find unique stuffs.
{
	object where;
	mixed *obs;
	string str;
	int i;

	remove_call_out("find_unique");
	call_out("find_unique", 120+random(CALLOUT_TICK));
	reclaim_objects();
	obs = filter_array(objects(), (: filtdata :));

	i = sizeof(obs);
	if(!i) return;
/* ��Ҫ�Զ� reclaim�������д���Ҳ���ֲ��ˡ�
	i = sizeof(obs);
	while (i--)
	if (!environment(obs[i]) && !interactive(obs[i]) && !obs[i]->query_temp("body_ob")) {
		reset_eval_cost();
		destruct(obs[i]);
		obs -= ({ 0 });
		i = sizeof(obs);
	}
	
	if(!obs || sizeof(obs) < 1 ) return;
*/
	where = environment(obs[i=random(i)]);

	if (environment(where))
		while( environment(where)->is_character() )
			where = (environment(where));
	
	if(where->is_character()) {
		str = TASK_D->get_regions(base_name(environment(where)));
		if( str == "" )
			str = "��ԭ";
		str = (!random(10)?where->query("name"):"����")+"����"+obs[i]->name(1)+ "��"+ str + "һ�����֣�";
	}
	else if(where->query("short"))
		str = "��˵"+obs[i]->name(1)+ "�������"+ TASK_D->get_regions(base_name(where)) + where->query("short") + "������";
	
	CHANNEL_D->do_channel(this_object(), "rumor", str);
}

// This is called everyday noon by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase
void event_sunrise()
{
	int i = localtime(TIME_TICK)[4];

	if (i != current_month) {
		message("outdoor:vision", month_time[i], users());
		current_month = i;
	}
}

string outdoor_room_description()
{
	return "����" + sprintf(
		day_phase[current_day_phase]["desc_msg"],
		month_desc[current_month]) + "��\n" NOR;
}

string game_time()
{
	return CHINESE_D->chinese_date(TIME_TICK);
}

// This function is to read a regular type of data table for day_phase and
// etc.
mapping *read_table(string file)
{
	string *line, *field, *format;
	mapping *data;
	int i, rn, fn;

	line = explode(read_file(file), "\n");
	data = ({});
	for(i=0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !pointerp(field) ) {
			field = explode( line[i], ":" );
			continue;
		}
		if( !pointerp(format) ) {
			format = explode( line[i], ":" );
			continue;
		}
		break;
	}

	for( rn = 0, fn = 0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !fn ) data += ({ allocate_mapping(sizeof(field)) });
		sscanf( line[i], format[fn], data[rn][field[fn]] );
		fn = (++fn) % sizeof(field);
		if( !fn ) ++rn;
	}
	return data;
}

mapping *query_day_phase() { return day_phase; }
void event_night()
{
	object badguy;
	object room;
        if (random(100) < 0)
        {
		if(objectp(room=load_object("/d/city/guangchang")) && 
		objectp(badguy = new("/quest/feizei/feizei")))
		badguy->move(room);
  message("channel:chat", HIW"���ٸ�ͨ�桿"HIR + "���ݳ��н�ҹ�з������У������������Ų�������Ī����\n"NOR,users() );
	}

        if (random(100) < 0)
        {
		if(objectp(room=load_object("/d/chengdu/dananmen")) && 
		objectp(badguy = new("/quest/feizei/feizei")))
		badguy->move(room);
  message("channel:chat", HIW"���ٸ�ͨ�桿"HIR + "�ɶ����н�ҹ�з������У������������Ų�������Ī����\n"NOR,users() );
	}

        if (random(100) < 0)
        {
		if(objectp(room=load_object("/d/dali/beimen")) && 
		objectp(badguy = new("/quest/feizei/feizei")))
		badguy->move(room);
  message("channel:chat", HIW"���ٸ�ͨ�桿"HIR + "������н�ҹ�з������У������������Ų�������Ī����\n"NOR,users() );
	}
        if (random(100) < 0)
        {
		if(objectp(room=load_object("/d/foshan/dongmen")) && 
		objectp(badguy = new("/quest/feizei/feizei")))
		badguy->move(room);
  message("channel:chat", HIW"���ٸ�ͨ�桿"HIR + "��ɽ���н�ҹ�з������У������������Ų�������Ī����\n"NOR,users() );
	}
        if (random(100) == 6)
        {
		if(objectp(room=load_object("/d/fuzhou/nanmen")) && 
		objectp(badguy = new("/quest/feizei/feizei")))
		badguy->move(room);
  message("channel:chat", HIW"���ٸ�ͨ�桿"HIR + "���ݳ��н�ҹ�з������У������������Ų�������Ī����\n"NOR,users() );
	}
        if (random(100) < 0)
        {
		if(objectp(room=load_object("/d/hz/beimen")) && 
		objectp(badguy = new("/quest/feizei/feizei")))
		badguy->move(room);
  message("channel:chat", HIW"���ٸ�ͨ�桿"HIR + "���ݳ��н�ҹ�з������У������������Ų�������Ī����\n"NOR,users() );
	}
        if (random(100) < 0)
        {
		if(objectp(room=load_object("/d/ningbo/ningbocheng")) && 
		objectp(badguy = new("/quest/feizei/feizei")))
		badguy->move(room);
  message("channel:chat", HIW"���ٸ�ͨ�桿"HIR + "�������н�ҹ�з������У������������Ų�������Ī����\n"NOR,users() );
	}
        if (random(100) < 0)
        {
		if(objectp(room=load_object("/d/suzhou/southgate")) && 
		objectp(badguy = new("/quest/feizei/feizei")))
		badguy->move(room);
  message("channel:chat", HIW"���ٸ�ͨ�桿"HIR + "���ݳ��н�ҹ�з������У������������Ų�������Ī����\n"NOR,users() );
	}
        if (random(100) < 0)
        {
		if(objectp(room=load_object("/d/xiangyang/zhuquemen")) && 
		objectp(badguy = new("/quest/feizei/feizei")))
		badguy->move(room);
  message("channel:chat", HIW"���ٸ�ͨ�桿"HIR + "�������н�ҹ�з������У������������Ų�������Ī����\n"NOR,users() );
	}

}


