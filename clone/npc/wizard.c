// wizardb.c

#include <ansi.h>
#include <localtime.h>

inherit NPC;

int ask_name();
int ask_guild();
int ask_me_1();
int ask_fy();
int ask_cgift();
int ask_sjsz();
int ask_duihuan();
private void set_enter_date(object ob,int date);
private int query_date(int date);

void create()
{
	set_name("��ʦ",({  "wizard", "wushi" }) );
        set("gender", "����" );
        set("age", 30);
        set("long", "����һ�������������µ���ʦ�������ѯ����������é®�������Խ�ɽׯ���������Ե������������ֶһ����͡���Դ�������⡣\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);
        set_temp("apply/defense", 10);
        set("combat_exp", 100);
        set("attitude", "peaceful");
        set("inquiry", ([
	"name": (: ask_name :),
	"����é®": (: ask_me_1 :),
//              "��վ����": (: ask_me_2 :),
                 "�Խ�ɽׯ": (: ask_sjsz :),
                "���Ե���": (: ask_cgift :),
                "���ֶһ�": (: ask_duihuan :),
                "��Դ": (: ask_fy :),
		"rumors": "��˵����Խ�����ϵͳ���뿪�Ž׶��ˡ�",
        	"bbb": "���������ң��ѵ�û���κα�ʾ��",
		"����": (:ask_guild :),
         	"ɱ��": "���������ң��ѵ�û���κα�ʾ��",
	]) );

        carry_object("/clone/misc/cloth")->wear();
        setup();
}

int ask_name()
{
	object ob = this_player();

	command("smash " + ob->query("id"));
	say("û���ɣ�һ�����Ծ�smash���ˣ�׼��BBB��\n");
	return 1;
}

int ask_fy()
{
	object me = this_player();
        int i;
        i = me->query("kar");
        command("say ��Ŀǰ�ĸ�Դ��" + chinese_number(i) + "��\n");
        return 1;
}

int ask_guild()
{
	object ob = this_player();
	int exp = ob->query("combat_exp");
	if (exp >= 2000000 && (!present("lingpai",ob)))
	{
          	new("/data/group/obj/ling")->move(ob);
		say("��ʦ˵������������ȥ�ɡ�����ϵͳ���н��顢BUG ���� bbb ���档\n");
	}
	if ( exp < 2000000 )
		say("��ʦ˵������ľ��鲻������ʱ���ܴ������ɡ�\n");
	if ( present("lingpai",ob))
		say("��ʦ˵�������Ѿ��������ˡ�\n");
	else	say("��ʦ˵�������������ϣ����ܴ������ɡ�\n");
	return 1;
}

int ask_me_1()
{
	object me = this_player();
	
	if( me->query("combat_exp") < 100000 ) {
		command("disapp "+(string)me->query("id"));
		command("say ��ľ��鲻�㣬���Ǽ���Ŭ���ɣ�\n");
		return 1;
	}

	if( me->query("gift_2013") ) {
		command("hmm "+(string)me->query("id"));
		command("say ���Ѿ���������ˡ�\n");
		return 1;
	}

	me->set("gift_2013", 1 );
	me->add("neili", 100 );
	me->add("max_neili", 100 );
	me->add("jingli", 100 );
	me->add("max_jingli", 100 );
        if( me->query_skill("force",1) > 80 ) {
         	me->add("balance", 2000000 );
	}
        me->setup();
	  me->add("potential", 2000 );
        me->add_busy(1 + random(2));
        write(HIY"����һ��"HIW"��������"HIY"�����˵������㵸����!\n"NOR);
        return 1;
}

int ask_sjsz()
{
        object ob,me,*thing;
        int i, time;
		int sysdate;
		
		me = this_player();

		//for old data
	if (me->query("sjsz_enter_time"))
	     set_enter_date(me,me->query("sjsz_enter_time"));

	if (me->query("sjsz_enter_time")=="2013119")
	     me->delete("sjsz_enter_time");

	ob = load_object("/clone/npc/zhong-shentong");


	if( me->query("id") == ob->query("winner") ) {
             command("say ����ͨ�ɲ���ȥ�Խ�ɽׯ��\n");
             return 1;
        }

        if( me->query_condition("killer") && !wiz_level(me) ) {
             command("say ͨ�����ɲ���ȥ�Խ�ɽׯ��\n");
             return 1;
        }
        if( me->query("balance") < 2000000 ) {
             command("say ������д��������ܽ����Խ�ɽׯ��\n");
             return 1;
        }
        if( me->query("combat_exp") < 2000000 ) {
	       command("disapp "+(string)me->query("id"));
		 command("say ��ľ��鲻�㣬���Ǽ���Ŭ���ɣ�\n");
		 return 1;
	  }
	sysdate=query_date(time());
	if( me->query("sjsz_enter_date") && sysdate <= me->query("sjsz_enter_date") ) {
             command("say һ��ֻ�ܽ����Խ�ɽׯһ�Σ������������ɡ�\n");
			  tell_object(me,HIG"���ϴν����Խ�ɽׯ����"+CHINESE_D->chinese_date(me->query("sjsz_enter_time"),1)+"��\n"NOR);
             return 1;
        }
	
		thing = deep_inventory(me);
		i = sizeof(thing);
	  while (i--)
	       if (thing[i]->is_character()) {
		   message_vision("��ʦͻȻ����һ�ɣ������㻹������˽�ȥ��\n", me);
	         command("knock "+(string)me->query("id"));
		   command("say �����������ɣ�\n");
		   me->add_busy(100 + random(200));
	         return 1;
		} 

        me->add("balance", -2000000);
        command("nod "+(string)me->query("id"));
        command("say �ðɣ������ھ�����ȥ�Խ�ɽׯ��\n");
        me->set("sjsz_enter_time",time());
		set_enter_date(me,time());
		


        me->apply_condition("sjsz_time",60);
        me->move("/cmds/leitai/bwdh/gate");
        CHANNEL_D->do_channel( this_object(), "rumor",
        sprintf("%s��ʼ�Խ�ɽׯ��ð���ˣ�", me->name(1)));
        return 1;
}
private void set_enter_date(object ob,int date)
{
		mixed *local;
		int y, m, d;
		string sjsz_enter_date;
		
		local = localtime(date);
		d = local[LT_MDAY];
		m = local[LT_MON];
		y = local[LT_YEAR];
		
		if (m<10) {
                  if (d<10)  
                          sjsz_enter_date=y+"0"+m+"0"+d;
		      else
			        sjsz_enter_date=y+"0"+m+d;
                  }
            else {
                  if (d<10)  
                          sjsz_enter_date=""+y+m+"0"+d;
		      else
			        sjsz_enter_date=""+y+m+d;
                  }

		ob->set("sjsz_enter_date",sjsz_enter_date);

}
private int query_date(int date)
{
		mixed *local;
		int y, m, d;
		string query_date;
		
		local = localtime(date);
		d = local[LT_MDAY];
		m = local[LT_MON];
		y = local[LT_YEAR];
		
		if (m<10) {
                  if (d<10)  
                          query_date=y+"0"+m+"0"+d;
		      else
		              query_date=y+"0"+m+d;
                  }
            else {
                  if (d<10)  
                          query_date=""+y+m+"0"+d;
		      else
			        query_date=""+y+m+d;
                  }

		return (int)query_date;

}

int ask_cgift()
{
	object me = this_player();
	if( me->query("combat_exp") < 100000 ) {
		command("disapp "+(string)me->query("id"));
		command("say ��ľ��鲻�㣬����Ŭ���ɣ�\n");
		return 1;
	}

	if( me->query("cgift_2013") ) {
		command("hmm "+(string)me->query("id"));
		command("say ���Ѿ��ʹ��ˣ���ô���ʰ���\n");
                me->add_busy(50);
		return 1;
	}

	me->set("cgift_2013", 1 );
        me->set_temp("cgift", 1 );
        me->add_busy(1 + random(2));
        write(HIY"���ѻ��һ��cgiftָ��ʹ�û��ᣬ��������ǰʹ��!�޸��������Խ���۳����飬������ʹ�ã�\n"NOR);
        return 1;
}

int ask_duihuan()
{
	object me = this_player();
	int i,time;

        time = time()- me->query("duihuan_time");

        if( me->query("duihuan_time") && time < 604800 ) {
             tell_object(me,HIG"��������ʦ��"+CHINESE_D->chinese_time(604800-time)+"֮�ڲ����������ڻ��ֶһ������⡣\n"NOR);
             return 1;
        }

        switch( random(8) ){
		case 0:	i = me->query("dali_job");
                        if (i > 500 ) {
                        	i = i - 500;
                        	me->add("dali_job",-500);
                        	me->add("sj_credit",20);
                        	command("say ��ʹ��500�δ���������������һ���20�㸱��������\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%sʹ��500�δ���������������һ���20�㸱��������", me->name(1)));
                        } else {
                        	command("say ��Ĵ������������������500�Σ����´�������\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 1:	i = me->query("hs_job");
                        if (i > 500 ) {
                        	i = i - 500;
                        	me->add("hs_job",-500);
                        	me->add("sj_credit",20);
                        	command("say ��ʹ��500�λ�ɽ��������һ���20�㸱��������\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%sʹ��500�λ�ɽ��������һ���20�㸱��������", me->name(1)));
                        } else {
                        	command("say ��Ļ�ɽ�����������500�Σ����´�������\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 2:	i = me->query("job_time/���ְ�");
                        if (i > 400 ) {
                        	i = i - 400;
                        	me->add("job_time/���ְ�",-400);
                        	me->add("sj_credit",20);
                        	command("say ��ʹ��400�γ��ְ���������һ���20�㸱��������\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%sʹ��400�γ��ְ���������һ���20�㸱��������", me->name(1)));
                        } else {
                        	command("say ��ĳ��ְ������������400�Σ����´�������\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 3:	i = me->query("wd_job");
                        if (i > 400 ) {
                        	i = i - 400;
                        	me->add("wd_job",-400);
                        	me->add("sj_credit",20);
                        	command("say ��ʹ��400���䵱��������һ���20�㸱��������\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%sʹ��400���䵱��������һ���20�㸱��������", me->name(1)));
                        } else {
                        	command("say ����䵱�����������400�Σ����´�������\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 4:	i = me->query("xs_job");
                        if (i > 400 ) {
                        	i = i - 400;
                        	me->add("xs_job",-400);
                        	me->add("sj_credit",20);
                        	command("say ��ʹ��400��ѩɽ��������һ���20�㸱��������\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%sʹ��400��ѩɽ��������һ���20�㸱��������", me->name(1)));
                        } else {
                        	command("say ���ѩɽ�����������400�Σ����´�������\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 5:	i = me->query("gb_job");
                        if (i > 300 ) {
                        	i = i - 300;
                        	me->add("gb_job",-300);
                        	me->add("sj_credit",20);
                        	command("say ��ʹ��300��ؤ���ⳤ����������һ���20�㸱��������\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%sʹ��300��ؤ���ⳤ����������һ���20�㸱��������", me->name(1)));
                        } else {
                        	command("say ���ؤ���ⳤ�������������300�Σ����´�������\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 6:	i = me->query("songshan_point");
                        if (i > 300 ) {
                        	i = i - 300;
                        	me->add("songshan_point",-300);
                        	me->add("sj_credit",20);
                        	command("say ��ʹ��300����ɽ��������һ���20�㸱��������\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%sʹ��300����ɽ��������һ���20�㸱��������", me->name(1)));
                        } else {
                        	command("say �����ɽ�����������300�Σ����´�������\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 7:	i = me->query("gb_job4");
                        if (i > 100 ) {
                        	i = i - 100;
                        	me->add("songshan_point",-100);
                        	me->add("sj_credit",20);
                        	command("say ��ʹ��100��ؤ����Ħ����������һ���20�㸱��������\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%sʹ��100��ؤ����Ħ����������һ���20�㸱��������", me->name(1)));
                        } else {
                        	command("say ���ؤ����Ħ�������������100�Σ����´�������\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		default: break;
	}

	return 1;

}