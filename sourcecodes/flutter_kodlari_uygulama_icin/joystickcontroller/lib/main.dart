import 'package:flutter/material.dart';
import 'package:flutter_joystick/flutter_joystick.dart';
import 'package:http/http.dart' as http;
void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Joystick',
      theme: ThemeData(
        // This is the theme of your application.
        //
        // TRY THIS: Try running your application with "flutter run". You'll see
        // the application has a blue toolbar. Then, without quitting the app,
        // try changing the seedColor in the colorScheme below to Colors.green
        // and then invoke "hot reload" (save your changes or press the "hot
        // reload" button in a Flutter-supported IDE, or press "r" if you used
        // the command line to start the app).
        //
        // Notice that the counter didn't reset back to zero; the application
        // state is not lost during the reload. To reset the state, use hot
        // restart instead.
        //
        // This works for code too, not just values: Most code changes can be
        // tested with just a hot reload.
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const HomePage(title: 'Joystick Kontrol'),
    );
  }
}

class HomePage extends StatefulWidget {
  final String title; // title parametresini ekleyin
  const HomePage({super.key, required  this.title});


  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  double _xValue = 0.0;
  double _yValue = 0.0;
  String _yon = "Center";
  String _response = "OK";
  String ip="192.168.1.31:80/";
  String _handleJoystickUpdate(StickDragDetails details) {
    setState(() {
      _xValue = double.parse(details.x.toStringAsFixed(3));
      _yValue = double.parse(details.y.toStringAsFixed(3));
    });

    if(_xValue ==0 && _yValue==0)
      {
        print("Joystick Merkezde");
        return "Center";
      }
    else if(_xValue <=0.4 && _xValue>= -0.4 && _yValue<=1 && _yValue>=0.8)

      {
        print("Joystick aşağıda");
        return "Backward";

      }
    else if(_xValue <=0.90 && _xValue>= 0.4 && _yValue<=0.77 && _yValue>=0.50)

    {
      print("Joystick aşağı sağda");
      return "RightBackward";

    }
    else if(_xValue <=0.4 && _xValue>= -0.4 && _yValue<= -0.8 && _yValue>=-1)

    {
      print("Joystick yukarıda");
      return "Forward";

    }
    else if(_xValue <=0.85 && _xValue>= 0.50 && _yValue<= -0.614 && _yValue>=-0.815)

    {
      print("Joystick yukarı sağda");
      return "RightForward";

    }
    else if(_xValue <=1 && _xValue>= 0.94 && _yValue<= 0.3 && _yValue>=-0.16)

    {
      print("Joystick sağda");
      return "Right";

    }
    else if(_xValue <=-0.6 && _xValue>= -1 && _yValue<= 0.463 && _yValue>=-0.4)

    {
      print("Joystick solda");
      return "Left";

    }
    else if(_xValue <=-0.5 && _xValue>= -0.8 && _yValue<= -0.463 && _yValue>=-0.9)

    {
      print("Joystick yukarıda solda");
      return "LeftForward";

    }
    else if(_xValue <=-0.5 && _xValue>= -0.81 && _yValue<= 0.85 && _yValue>=0.5)

    {
      print("Joystick aşağıda solda");
      return "LeftBackward";
    }
    else return "Center";

  }
  Future<void> sendGetRequest(String url) async {
    try {
      print("url: ${url}  ");
      print(Uri.parse(url));
      final response = await http.get(Uri.parse(url));

      if (response.statusCode == 200) {
        print('GET request successful');
        print('Response: ${response.body}');
        setState(() {
          _response = "OK, Status code: ${response.body}";
        });
      } else {
        print('GET request failed. Status code: ${response.statusCode}');
        setState(() {
          _response = "ERROR, Status code: ${response.statusCode}";
        });
      }
    } catch (e) {
      print('Error during GET request: $e');
      setState(() {
        _response = "ERROR, Error Code: ${e}";
      });
    }
  }
  @override
  Widget build(BuildContext context) {
    return
        Scaffold(
          appBar: AppBar(
            title: Text(widget.title),
          ),
          body:
          Column(mainAxisAlignment: MainAxisAlignment.center,children: [
            Center(
              child: Joystick(listener: (StickDragDetails details) {
                print("X: ${_xValue} Y: ${_yValue}");
               setState(() {
                  _yon = _handleJoystickUpdate(details);
               });
               sendGetRequest("http://${ip}${_yon}");


              },),
            ),
            SizedBox(height: 20,),
            Text("X: ${_xValue} Y: ${_yValue}, Yön: ${_yon}"),
            SizedBox(height: 20,),
            Text("Status:${_response}"),
          ],)
        );
  }
}

