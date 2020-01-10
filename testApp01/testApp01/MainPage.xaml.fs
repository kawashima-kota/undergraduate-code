namespace testApp01

open Xamarin.Forms
open Xamarin.Forms.Xaml
open System

type MainPage() =
    inherit ContentPage()    
    let _ = base.LoadFromXaml(typeof<MainPage>)

    let entry = Entry(Placeholder = "数を入力してください")
    let button = Button(Text ="平方根を計算する")
    
    let updateEntry s =
        entry.Text <- s

    let tryFloat x =
        match System.Double.TryParse x with
        | true, x -> Ok x
        | false, _ -> Error (sprintf "%sを変換することができませんでした" x)

    let toString (f: float) =
        string f

    let toSqrt x =
        match x with
        | x when x < 0. -> Error (sprintf "%fは負の数なので計算できません" x)
        | _ -> Ok (Math.Sqrt x)

    let calculate _ =
        entry.Text 
        |> tryFloat 
        |> Result.bind toSqrt
        |> Result.map toString
        |> function
            | Ok x -> updateEntry x
            | Error x -> updateEntry x

    do 
        button.Clicked.Add calculate
        let stack = StackLayout(VerticalOptions = LayoutOptions.CenterAndExpand)
        stack.Children.Add entry
        stack.Children.Add button
        base.Content <- stack