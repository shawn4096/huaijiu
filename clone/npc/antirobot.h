// Modified by snowman@SJ 12/06/2000

#define DROP_CMD		"/cmds/std/drop"

object ob;
int timer = 0;

// add by snowman@SJ 12/06/2000, ��ֹplayer flood hitting this npc.
int is_corpse(){ return 1; }
void move_to_court(object ob);
void test_robot(object obj);
void question();

void create()
{
	set_name("����ɱ��", ({ "blade runner", "runner" }));

	set("gender", "����");
	set("age", 20);
	set("no_quest", 1);
	set("no_drop", 1);
	set("no_get", 1);
	set_temp("apply/long",
		({ "����һ��ר��׷�������˵Ļ���̽Ա��\n"
		"������û����Զ��ش����⣬��������������ɾ����\n"})
	);
	set_skill("dodge", 1000);
	set("max_qi", 10000);
	set("qi", 10000);
	set("max_jing", 10000);
	set("jing", 10000);

	set("combat_exp", 5000000);

	set("inquiry", ([
		"name": "�㻹�����й��򰡣�ר�Ļش�����ɣ�",
		"rumors": "��˵�л����˻��뱾MUD���ٺ٣��ҿ��ǻ��۽�ѽ��",
	]) );
	set("attitude", "friendly");
	set("env/invisibility", 1);

	setup();
	set_weight(0);
}

void init()
{
	if (environment() == ob) {
		question();
		add_action("do_answer", ({ "answer" }));
		add_action("wait", ({
			"quit", "learn", "chat", "rumor", "tell", "reply", "whisper", "post", "ask",
			"say", "party", "study", "sleep", "practice", "exercise", "respirate", "to",
			"mm", "party*", "chat*", "rumor*", "emote", "lingwu", "teach", "beep", "team" })
		);
	}
}

int wait()
{
	write("�Բ������Ȼش����⡣\n");
	return 1;
}

void kill_ob(object ob)
{
	ob->remove_killer(this_object());
	remove_killer(ob);
	message_vision("$N��ɥ�ط�������ɱ�ָ����������ս����\n", ob);
}

void unconcious()
{
	reincarnate();
	set("eff_qi", query("max_qi"));
	set("qi", query("max_qi"));
	set("eff_jing", query("max_jing"));
	set("jing", query("max_jing"));
	set("jingli", query("eff_jingli"));
	say("����ɱ����Ц��˵�������޵в����棡\n");
	command("hehe");
}

void die()
{
	unconcious();
}

// ��ֹplayer����bug����������Ʒ�� by snowman@SJ 12/06/2000
//�ĳ��ڷ�ͥ����һ��ʱ��,��drop all,��ô��ʧ����  by tiantian@sj 7/8/2000
void move_to_court(object ob)
{
	string room;
	int times;

	ob->apply_condition("robot", 15);
	message_vision("$N��$n��ȥ�˷�ͥ��\n", this_object(), ob);
	if( !stringp(room = base_name(environment(ob))) ){
		if (ob->query("enter_wuguan"))
			room = "/d/wuguan/dayuan";
		else    room = "/d/city/chmiao";
	}
	if ( ob->query("robot") < 2 ) {
		ob->set("catch_robot_place", room);
		ob->move("/d/wizard/robot_court");
		tell_object(ob,"���Ѿ��ۻ�������ɱ��ץ�ͻ����˷�ͥ"+chinese_number(ob->add("robot",1))+"���ˡ�\n");
	} else{
		ob->delete("robot");
		times = ob->add("rules",1);
		ob->set("relax_timeout_room",room);
		ob->apply_condition("relax", times*30);
		tell_object(ob,"����Ϊ�������ˡ���Υ���齣��Ϸ���򹲼�" + chinese_number(times) +
			"�Σ���������ؽ������һ�Դ"+chinese_number(times*10)+"���ӵĴ�����\n");

		shout(HIW "\n�����ɡ�"+ob->query("name")+"("+capitalize(ob->query("id"))
			+")��Ϊ�������ˡ���Υ���齣��Ϸ���򹲼�"
			+chinese_number(times)+ "�Σ���������ؽ���"+chinese_number(times*10)+"���ӵĴ�����\n\n" NOR);

		tell_object(ob, "����ɱ�ְ���ֱ��ץ�����һ�Դ��\n");
		ob->move("/d/wizard/relax");
		log_file("static/ROBOT", sprintf("%s %s(%s)����Υ�� %d �Ρ�\n",
			ctime(time())[0..15],  ob->query("name"), ob->query("id"), times));
	}
}

void test1()
{
	object me = this_object();

	if (ob) {
		timer -= 10;
		if (timer > 0) {
			message("channel", "����ɱ�־����㣺�㻹��" + chinese_number(timer) + "���ӵĿ���ʱ�䡣\n", ob);
			me->move(ob, 1);
			call_out("test1", 10);
		} else {
			if (!interactive(ob) || query_idle(ob) >= 180) {
				"/cmds/usr/quit"->main(ob);
				if (me) destruct(me);
			} else {
				// ��ֹplayer�����ε���bug. snowman@SJ 12/06/2000.
				if (!living(ob)) ob->revive();
				message_vision(
					query("name")+"̾�˿�������$Nһ�㷴Ӧ��û�У�����һ���������ӷ���\n", ob
				);
				move_to_court(ob);
				destruct(me);
			}
		}
	}
	else destruct(me);
}

void test_player(string player)
{
	object ob = find_player(player);

	if (ob) test_robot(ob);
}
