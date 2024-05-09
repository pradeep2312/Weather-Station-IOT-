const Card = (props) => {
    return (
      <div className="card">
        <h2 className="heading">{props.heading}</h2>

        <div className="number">{props.number} {props.degree}</div>
      </div>
    );
  };

export default Card;